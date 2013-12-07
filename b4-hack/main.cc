// Copyright 2013 Karl Skomski - GPL v3

#include "utils\vmthooks.h"
#include "utils\utils.h"
#include "fb\core\WeakPtr.h"
#include "fb\core\RefArray.h"
#include "eastl\eastl.h"
#include "bf4-classes.h"
#include "renderer.h" 

using namespace DirectX;

Dx11Renderer    m_pDx11Renderer;

HANDLE thread = nullptr;
bool active_thread = true;

typedef WeaponFiring* (__cdecl* GetWeaponFiring)(ClientPlayer*, int);
typedef void(__thiscall* SendClientSpottingMessage)(ClientSpottingComponent*, ClientPlayer*, SpotType type, eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>*, ClientSoldierEntity* unknown);

utils::VtableHook* hook = nullptr;
utils::VtableHook* swapchain_hook = nullptr;
ClientGameContext* game_context = nullptr;
Main* main = nullptr;
DxRenderer* dx_renderer = nullptr;
GameRenderer* game_renderer = nullptr;
CameraManager* camera_manager = nullptr;

GetWeaponFiring getWeaponFiring;
float GetDistance(const XMVECTOR& v1, const XMVECTOR& v2);
bool GetBonePosition(ClientSoldierEntity* soldier, UpdatePoseResultData::BONES bone_id, DirectX::XMFLOAT3* position);

float closest_distance = 0;
ClientPlayer* closest_player;
float best_angle = 0;
GameWorld* client_game_world = nullptr;

bool WorldToScreen(DirectX::XMFLOAT3* world_position, DirectX::XMFLOAT2* screen_position) {
  if (!world_position || !screen_position) return 0;

  DirectX::XMFLOAT4X4 view_projection = game_renderer->view->view_projection_matrix;

  int screen_x = dx_renderer->screen->width * 0.5;
  int screen_y = dx_renderer->screen->height * 0.5;

  float w = view_projection.m[0][3] * world_position->x + view_projection.m[1][3] * world_position->y + view_projection.m[2][3] * world_position->z + view_projection.m[3][3];
  if (w < 0.19)  return false;
  float x = view_projection.m[0][0] * world_position->x + view_projection.m[1][0] * world_position->y + view_projection.m[2][0] * world_position->z + view_projection.m[3][0];
  float y = view_projection.m[0][1] * world_position->x + view_projection.m[1][1] * world_position->y + view_projection.m[2][1] * world_position->z + view_projection.m[3][1];

  screen_position->x = screen_x + screen_x * x / w;
  screen_position->y = screen_y - screen_y * y / w;

  return true;
}


static bool IsVisible(DirectX::XMVECTOR* from, DirectX::XMVECTOR* target) {
  if (!from || !target) return false;

  IPhysicsRayCaster* ray_caster = &client_game_world->ray_caster;
  if (!ray_caster) return false;

  RayCastHit ray;

  bool is_visible = !ray_caster->PhysicsRayQuery(
      "controllableFinder", from, target, &ray,
      IPhysicsRayCaster::DontCheckWater | IPhysicsRayCaster::DontCheckRagdoll |
      IPhysicsRayCaster::DontCheckCharacter | IPhysicsRayCaster::DontCheckPhantoms, NULL);

  return is_visible;
}

bool IsInsideFOV(XMVECTOR& dist, float max_fov) {

  XMVECTOR forward = game_renderer->view->view_matrix.r[2];

  if (XMVector3Dot(dist, forward).m128_f32[0] < cos(((max_fov / 2.0f) * (3.141592741012573f / 180.0f))))
    return false;

  return true;
}

bool PredictAim(ClientSoldierEntity* target, XMFLOAT3* result_position) {
  if (!target || !result_position) return false;

  auto local_soldier = game_context->client_player_manager_->local_player_->m_soldier.getData();
  if (!local_soldier) return false;

  DirectX::XMFLOAT3 head;
  if (!GetBonePosition(target, UpdatePoseResultData::BONES::BONE_SPINE, &head)) return false;
  XMVECTOR head_vector = XMLoadFloat3(&head);

  if (!GetBonePosition(local_soldier, UpdatePoseResultData::BONES::BONE_RIGHTHAND, &head)) return false;
  XMVECTOR own_head_vector = XMLoadFloat3(&head);

  WeaponFiring* weapon_firing = getWeaponFiring(game_context->client_player_manager_->local_player_, 0);

  if (weapon_firing == nullptr ||
    weapon_firing->weapon_firing_data == nullptr ||
    weapon_firing->weapon_firing_data->primary_fire == nullptr) {
    return false;
  }
  float distance = GetDistance(head_vector, own_head_vector);

  float gravity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_ProjectileData->gravity;
  float velocity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_InitialSpeed.z;

  head_vector = head_vector + XMLoadFloat3(target->GetVelocity()) * (distance / fabs(velocity));
  head_vector = head_vector - XMLoadFloat3(local_soldier->GetVelocity()) * (distance / fabs(velocity));
  FLOAT m_grav = fabs(gravity);
  FLOAT m_dist = distance / fabs(velocity);
  head_vector.m128_f32[1] += 0.5 * m_grav * m_dist * m_dist;

  head_vector = XMVectorSubtract(head_vector, own_head_vector);
  XMStoreFloat3(result_position, head_vector);
  return true;
}

#define D3DXToDegree(radian) ((radian) * (180.0f / D3DX_PI))

ClientPlayer* IdentifyTarget(ClientPlayer* local_player) {
  auto players = game_context->client_player_manager_->getPlayers();

  closest_distance = 300;
  closest_player = nullptr;
  best_angle = 0;

  XMMATRIX transform;
  local_player->m_soldier.getData()->GetTransform(&transform);
  XMVECTOR local_soldier_position = transform.r[3];

  for (size_t i = 0; i < players->size(); i++) {
    ClientPlayer *player = players->at(i);

    if (player == nullptr) {
      continue;
    }

    if (player->team_id == 0 || player->team_id == local_player->team_id) continue;

    ClientSoldierEntity* soldier_entity = player->m_soldier.getData();

    if (soldier_entity == nullptr   ) {
      continue;
    }

    DirectX::XMFLOAT3 head;

    if (!GetBonePosition(soldier_entity, UpdatePoseResultData::BONES::BONE_RIGHTHAND, &head)) continue;
    XMVECTOR head_vector = XMLoadFloat3(&head);

    if (!GetBonePosition(local_player->m_soldier.getData(), UpdatePoseResultData::BONES::BONE_RIGHTHAND, &head)) continue;
    XMVECTOR own_head_vector = XMLoadFloat3(&head);


    XMVECTOR diff = XMVectorSubtract(head_vector, own_head_vector);

    diff = XMVector3Normalize(diff);

    float DotProduct = D3DXToDegree(cos(XMVector3Dot(game_renderer->view->transform.r[2], diff).m128_f32[0]));
    best_angle = DotProduct;
    if (DotProduct <= 8) {
      float distance = GetDistance(head_vector, own_head_vector);
      if (distance < closest_distance && IsVisible(&own_head_vector, &head_vector)) {
          closest_player = player;
          closest_distance = distance;
        }
   }
 }

  return closest_player;
}


float AimFloat(XMVECTOR &src, XMVECTOR &delta, const float &FOV) {
  return asinf(XMVector3Dot(src, delta).m128_f32[0]) / FOV;
}

ClientControllableEntity* GetTargetInAim() {
  ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
  if (!local_player) return nullptr;

  ClientControllableEntity* entity = nullptr;

  if (local_player->InVehicle()) {
    fb::EntryComponent* entry = local_player->GetEntryComponent();
    if (!entry) return nullptr;

    int stance = entry->GetActiveStance();
    fb::ClientWeapon* weapon = nullptr;

    auto weapons = entry->weapons;
    for (int i = 0; i < weapons.size(); i++) {
      auto weapon_callbacks = weapons.at(i);
      if (!weapon_callbacks || !weapon_callbacks->weapon_info) continue;

      if (weapon_callbacks->weapon_info->ActiveInStance(stance)) {
        weapon = weapon_callbacks->weapon_info->GetWeapon();
        break;
      }
    }

    if (weapon) {
      entity = weapon->finder.in_aim.getData();
    }
  }
  return entity;
}

void __fastcall Update(Main *thisptr, void* edx, float delta) {
  typedef void(__thiscall* OrgMethod)(void*, float);
  hook->GetMethod<OrgMethod>(3)(thisptr, delta);

  ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
  if (!local_player || !local_player->m_soldier.getData()) return;

  auto input_buffer = main->client->input_node->input_cache->input_buffer;

  if (false && GetAsyncKeyState(0x01)) {

    auto soldier = local_player->m_soldier.getData();
    if (!soldier) return;
    auto weapons = (fb::ClientSoldierWeaponsComponent*)soldier->components->GetFirstComponentOfType(fb::ClientSoldierWeaponsComponent::CLASS_ID, fb::ClientSoldierWeaponsComponent::CLASS_ID);
    auto weapon = weapons->GetActiveSoldierWeapon();
    if (weapon && weapon->weapon) {
      ClientPlayer* player = IdentifyTarget(local_player);
      if (player && player->m_soldier.getData()) {
        XMFLOAT3 head_position;
        if (PredictAim(player->m_soldier.getData(), &head_position)) {
          XMVECTOR vec = XMVector3Normalize(XMLoadFloat3(&head_position));

          float yaw = -atan2(vec.m128_f32[0], vec.m128_f32[2]);
          float pitch = atan2(vec.m128_f32[1], sqrt(pow(vec.m128_f32[0], 2) + pow(vec.m128_f32[2], 2)));
          weapon->authorative_aiming->fps_aimer->pitch = pitch;
          weapon->authorative_aiming->fps_aimer->yaw = yaw;
          //input_buffer[InputConceptIdentifiers::ConceptFire] = 1.0f;
        }
      }
    }
  }

  //if (local_player->InVehicle()) {
  //  fb::EntryComponent* entry = local_player->GetEntryComponent();
  //  if (!entry) return;

  //  int stance = entry->GetActiveStance();
  //  fb::ClientWeapon* weapon = nullptr;

  //  auto weapons = entry->weapons;
  //  for (int i = 0; i < weapons.size(); i++) {
  //    auto weapon_callbacks = weapons.at(i);
  //    if (!weapon_callbacks || !weapon_callbacks->weapon_info) continue;

  //    if (weapon_callbacks->weapon_info->ActiveInStance(stance)) {
  //      weapon = weapon_callbacks->weapon_info->GetWeapon();
  //      break;
  //    }
  //  }

  //  if (weapon) {
  //    auto entity = weapon->finder.in_aim.getData();
  //    if (!entity) return;
  //    if (entity->getType()->class_id == 668) {
  //      auto vehicle = (ClientVehicleEntity*)entity;
  //      XMMATRIX transform;
  //      vehicle->GetTransform(&transform);
  //      XMFLOAT3 center = vehicle->children_aabb.GetCenter();
  //      XMVECTOR center_world = XMVector3Transform(XMLoadFloat3(&center), transform);

  //      XMVECTOR left = game_renderer->view->transform.r[0];
  //      XMVECTOR up = game_renderer->view->transform.r[1];
  //      XMVECTOR origin = game_renderer->view->transform.r[3];

  //      XMVECTOR diff = XMVector3Normalize(XMVectorSubtract(center_world, game_renderer->view->transform.r[3]));

  //      WeaponFiring* weapon_firing = getWeaponFiring(local_player, 0);

  //      if (weapon_firing == nullptr ||
  //        weapon_firing->weapon_firing_data == nullptr ||
  //        weapon_firing->weapon_firing_data->primary_fire == nullptr) {
  //        return;
  //      }

  //      float gravity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_ProjectileData->gravity;
  //      float velocity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_InitialSpeed.z;

  //      float drop = abs(pow((sqrt(pow(diff.m128_f32[0], 2) + pow(diff.m128_f32[1], 2) + pow(diff.m128_f32[2], 2)) / velocity), 2) * 0.5 * gravity);

  //      diff.m128_f32[1] += drop;

  //      XMVECTOR vec = XMVector3Normalize(diff);

  //      float yaw = AimFloat(left, vec, game_renderer->view->fovX / 2.0f);
  //      float pitch = AimFloat(up, vec, game_renderer->view->fovX / 2.0f);
  //      float roll = yaw;

  //      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptYaw] = yaw * 8;
  //      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptPitch] = pitch * 8;
  //      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptRoll] = roll * 8;
  //    }
  //  }
  //}
  //else {
  //  auto soldier = local_player->m_soldier.getData();
  //  if (!soldier) return;
  //  auto weapons = (fb::ClientSoldierWeaponsComponent*)soldier->components->GetFirstComponentOfType(fb::ClientSoldierWeaponsComponent::CLASS_ID, fb::ClientSoldierWeaponsComponent::CLASS_ID);
  //  auto weapon = weapons->GetActiveSoldierWeapon();
  //  if (weapon && weapon->weapon) {
  //    auto entity = weapon->weapon->finder.in_aim.getData();

  //    if (!entity) return;
  //    //if (entity->team_id > 0 && entity->team_id != local_player->team_id) return;
  //    if (entity->getType()->class_id == 668) {
  //      auto vehicle = (ClientVehicleEntity*)entity;
  //      XMMATRIX transform;
  //      vehicle->GetTransform(&transform);
  //      XMFLOAT3 center = vehicle->children_aabb.GetCenter();
  //      XMVECTOR center_world = XMVector3Transform(XMLoadFloat3(&center), transform);

  //      XMVECTOR diff = XMVectorSubtract(center_world, game_renderer->view->transform.r[3]);

  //      WeaponFiring* weapon_firing = getWeaponFiring(local_player, 0);

  //      if (weapon_firing == nullptr ||
  //        weapon_firing->weapon_firing_data == nullptr ||
  //        weapon_firing->weapon_firing_data->primary_fire == nullptr) {
  //        return;
  //      }
  //      float gravity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_ProjectileData->gravity;
  //      float velocity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_InitialSpeed.z;

  //      float drop = abs(pow((sqrt(pow(diff.m128_f32[0], 2) + pow(diff.m128_f32[1], 2) + pow(diff.m128_f32[2], 2)) / velocity), 2) * 0.5 * gravity);
  //      diff.m128_f32[1] += drop;

  //      XMVECTOR vec = XMVector3Normalize(diff);

  //      float yaw = -atan2(vec.m128_f32[0], vec.m128_f32[2]);
  //      float pitch = atan2(vec.m128_f32[1], XMVector3Length(vec).m128_f32[0]);
  //      weapon->authorative_aiming->fps_aimer->pitch = pitch;
  //      weapon->authorative_aiming->fps_aimer->yaw = yaw;
  //      //main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptFire] = 1.0f;
  //    }
  //    else {
  //      DirectX::XMFLOAT3 head;

  //      if (GetBonePosition((ClientSoldierEntity*)entity, UpdatePoseResultData::BONES::BONE_HEAD, &head)) {
  //        DirectX::XMVECTOR head_vector = DirectX::XMLoadFloat3(&head);

  //        XMVECTOR diff = XMVectorSubtract(head_vector, game_renderer->view->transform.r[3]);

  //        WeaponFiring* weapon_firing = getWeaponFiring(local_player, 0);

  //        if (weapon_firing == nullptr ||
  //          weapon_firing->weapon_firing_data == nullptr ||
  //          weapon_firing->weapon_firing_data->primary_fire == nullptr) {
  //          return;
  //        }
  //        float gravity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_ProjectileData->gravity;
  //        float velocity = weapon_firing->weapon_firing_data->primary_fire->shot_config_data.m_InitialSpeed.z;

  //        float drop = abs(pow((sqrt(pow(diff.m128_f32[0], 2) + pow(diff.m128_f32[1], 2) + pow(diff.m128_f32[2], 2)) / velocity), 2) * 0.5 * gravity);
  //        diff.m128_f32[1] += drop;

  //        XMVECTOR vec = XMVector3Normalize(diff);

  //        float yaw = -atan2(vec.m128_f32[0], vec.m128_f32[2]);
  //        float pitch = atan2(vec.m128_f32[1], XMVector3Length(vec).m128_f32[0]);
  //        weapon->authorative_aiming->fps_aimer->pitch = pitch;
  //        weapon->authorative_aiming->fps_aimer->yaw = yaw;
  //        input_buffer[InputConceptIdentifiers::ConceptFire] = 1.0f;
  //      }
  //    }
  //  }
  //}
  //input_buffer[InputConceptIdentifiers::ConceptBreathControl] = 1.0f;

  if (local_player != nullptr && local_player->vehicle) {
    char* name = local_player->vehicle->GetPhysiscsEntity()->data->asset->name.chars;
    if (strstr(name, "F35") || strstr(name, "A-10") || strstr(name, "SU") ||
      strstr(name, "fantan") || strstr(name, "J-20")) {
      float speed = local_player->vehicle->GetVelocity()->GetMagnitude()* 3.6f;

      if (speed <= 308 && speed > 20) {
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveFB] = 1.0f;
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveForward] = 1.0f;
      }
      else if (speed >= 312 && speed > 20) {
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveFB] = -1.0f;
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveBackward] = 1.0f;
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptCrawl] = 1.0f;
        main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptBrake] = 1.0f;
      }
    }
  }
}

bool GetBonePosition(ClientSoldierEntity* soldier, UpdatePoseResultData::BONES bone_id, DirectX::XMFLOAT3* position) {
  if (!soldier || !bone_id) return false;

  auto bone_component = (fb::ClientRagdollComponent*)soldier->components->GetFirstComponentOfType(fb::ClientRagdollComponent::CLASS_ID, fb::ClientRagdollComponent::CLASS_ID);
  if (!bone_component) return false;
  if (!bone_component->skeleton) return false;
  if (!bone_component->pose_result_data.valid_transforms) return false;

  auto ant_component = (fb::ClientAntAnimatableComponent*)soldier->components->GetFirstComponentOfType(fb::ClientAntAnimatableComponent::CLASS_ID, fb::ClientAntAnimatableComponent::CLASS_ID);
  if (!ant_component) return false;

  ant_component->had_visual_update = true;

  if (bone_id >= 0 && bone_id < bone_component->skeleton->bone_count) {
    *position = *(DirectX::XMFLOAT3*)&bone_component->pose_result_data.active_world_transforms[bone_id].trans_and_scale;
    return true;
  }
  return false;
}

float GetDistance(const XMVECTOR& v1, const XMVECTOR& v2) {
  XMVECTOR vectorSub = XMVectorSubtract(v1, v2);
  XMVECTOR length = XMVector3Length(vectorSub);

  float distance = 0.0f;
  XMStoreFloat(&distance, length);
  return distance;
}

float GetMagnitude(XMVECTOR* vector) {
  return sqrtf(vector->m128_f32[0] * vector->m128_f32[0] + vector->m128_f32[1] * vector->m128_f32[1] + vector->m128_f32[2] * vector->m128_f32[2]);
}

HRESULT WINAPI PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
  if (m_pDx11Renderer.IsRenderClassInitialized() == false) {
    m_pDx11Renderer.InitializeRenderClass(dx_renderer->device, dx_renderer->device_context);
  }
  ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
  if (!local_player) goto ret;


  if (local_player->vehicle) {
    float speed = local_player->vehicle->GetVelocity()->GetMagnitude()* 3.6f;
    m_pDx11Renderer._RenderText(50, 50, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "%f", speed);
  } else {
    auto soldier = local_player->m_soldier.getData();
    if (soldier) {
      XMVECTOR velocity = XMLoadFloat3(local_player->m_soldier.getData()->GetVelocity());
      float speed = GetMagnitude(&velocity) * 3.6f;
      m_pDx11Renderer._RenderText(50, 50, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "%f", speed);
    }
  }

  auto local_soldier = local_player->m_soldier.getData();
  if (local_soldier) {

    auto players = game_context->client_player_manager_->getPlayers();
    for (int i = 0; i < players->size(); i++) {
      ClientPlayer *player = players->at(i);

      if (player == nullptr || player->team_id == local_player->team_id) {
        continue;
      }
      AxisAlignedBox aab;
      DirectX::XMMATRIX transform;

      if (player->vehicle) {
        aab = player->vehicle->children_aabb;
        player->vehicle->GetTransform(&transform);
      }
      else {
        //auto soldier = player->m_soldier.getData();
        //if (!soldier || soldier->is_occluded) continue;

        //DirectX::XMFLOAT3 head;
        //if (GetBonePosition(soldier, UpdatePoseResultData::BONES::BONE_NOSETIP, &head)) {
        //  DirectX::XMVECTOR head_vector = DirectX::XMLoadFloat3(&head);
        //  DirectX::XMFLOAT2 screen;
        //  if (WorldToScreen(&head, &screen)) {
        //    m_pDx11Renderer.DrawBorder(screen.x, screen.y, 5, 5, 5, txtRed);
        //  }
        //}
      }

      //  DirectX::XMMATRIX transform;
      //    soldier->GetTransform(&transform);

      //   DirectX::XMMATRIX local_transform;
      //  local_soldier->GetTransform(&local_transform);

      //   //float distance = GetDistance(transform.r[3], local_transform.r[3]);
      //   //if (distance < 50) {

      //   if (soldier->physics_entity->current_pose == CharacterPoseType::Prone) {
      //     aab.min.x = -0.4f;
      //     aab.min.y = 0;
      //     aab.min.z = -1.6f;
      //     aab.max.x = 0.4f;
      //     aab.max.y = 0.35f;
      //     aab.max.z = 0.4f;
      //   }
      //   else if (soldier->physics_entity->current_pose == CharacterPoseType::Crouch) {
      //     aab.min.x = -0.4f;
      //     aab.min.y = 0;
      //     aab.min.z = -0.4f;
      //     aab.max.x = 0.4f;
      //     aab.max.y = 1.25f;
      //     aab.max.z = 0.4f;
      //   }
      //   else  {
      //     aab.min.x = -0.4f;
      //     aab.min.y = 0;
      //     aab.min.z = -0.4f;
      //     aab.max.x = 0.4f;
      //     aab.max.y = 1.7f;
      //     aab.max.z = 0.4f;
      //   }
      //   //}
      // }
      if (aab.min.x != 0) {
        XMFLOAT3 corners[8];
        aab.GetAllCorners(corners);
        XMFLOAT2 out[8];
        for (int i = 0; i < 8; i++) {
          XMFLOAT3 world_position;
          world_position.x = transform.r[0].m128_f32[0] * corners[i].x + transform.r[1].m128_f32[0] * corners[i].y + transform.r[2].m128_f32[0] * corners[i].z + transform.r[3].m128_f32[0];
          world_position.y = transform.r[0].m128_f32[1] * corners[i].x + transform.r[1].m128_f32[1] * corners[i].y + transform.r[2].m128_f32[1] * corners[i].z + transform.r[3].m128_f32[1];
          world_position.z = transform.r[0].m128_f32[2] * corners[i].x + transform.r[1].m128_f32[2] * corners[i].y + transform.r[2].m128_f32[2] * corners[i].z + transform.r[3].m128_f32[2];
          if (WorldToScreen(&world_position, &out[i]) == false) break;
        }

        // Top
        m_pDx11Renderer.DrawLine(out[5].x, out[5].y, out[1].x, out[1].y, txtRed);
        m_pDx11Renderer.DrawLine(out[1].x, out[1].y, out[2].x, out[2].y, txtRed);
        m_pDx11Renderer.DrawLine(out[2].x, out[2].y, out[4].x, out[4].y, txtRed);
        m_pDx11Renderer.DrawLine(out[4].x, out[4].y, out[5].x, out[5].y, txtRed);
        // Front
        m_pDx11Renderer.DrawLine(out[7].x, out[7].y, out[4].x, out[4].y, txtRed);;
        m_pDx11Renderer.DrawLine(out[6].x, out[6].y, out[7].x, out[7].y, txtRed);
        m_pDx11Renderer.DrawLine(out[5].x, out[5].y, out[6].x, out[6].y, txtRed);
        // Right
        m_pDx11Renderer.DrawLine(out[2].x, out[2].y, out[3].x, out[3].y, txtRed);
        m_pDx11Renderer.DrawLine(out[3].x, out[3].y, out[7].x, out[7].y, txtRed);
        // Left
        m_pDx11Renderer.DrawLine(out[1].x, out[1].y, out[0].x, out[0].y, txtRed);
        m_pDx11Renderer.DrawLine(out[0].x, out[0].y, out[6].x, out[6].y, txtRed);
        // Bottom
        m_pDx11Renderer.DrawLine(out[0].x, out[0].y, out[3].x, out[3].y, txtRed);
      }
    }
  }
    //  }
  //}

  //auto entity = GetTargetInAim();
  //if (entity && entity->getType()->class_id == 668) {
  //  auto vehicle = (ClientVehicleEntity*)entity;
  //  DirectX::XMMATRIX transform;
  //  vehicle->GetTransform(&transform);

  //  XMFLOAT3 center = vehicle->children_aabb.GetCenter();
  //  XMVECTOR world_position = XMVector3Transform(XMLoadFloat3(&center), transform);

  //  XMFLOAT2 screen_position;
  //  if (WorldToScreen((XMFLOAT3*)&world_position, &screen_position)) {
  //    m_pDx11Renderer.DrawBorder(screen_position.x, screen_position.y, 5 , 5, 5, txtRed);
  //  }
  //}
  m_pDx11Renderer._RenderText(10, 150, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "%f", best_angle);
  m_pDx11Renderer._RenderText(10, 100, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "%f", closest_distance);
  if (closest_player)
    m_pDx11Renderer._RenderText(10, 120, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "%i", closest_player->team_id);

  m_pDx11Renderer._RenderText(10, 10, D3DCOLOR_ARGB(255, 0, 184, 245), 18, FW1_RESTORESTATE, "active");

ret:
  typedef int(__stdcall* OrgMethod) (IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);
  return swapchain_hook->GetMethod<OrgMethod>(8)(SwapChain, SyncInterval, Flags);
}

DWORD WINAPI rec_thread(void* arguments) {
  //*(int*)0x203DAEC = 0;

  uint32_t screenshot_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x8B\x0D\x00\x00\x00\x00\x83\xEC\x18",
    "xx????xxx");
  if (screenshot_address == 0) {
    return 1;
  }

  // PBSS
  screenshot_address = *(uint32_t*)(screenshot_address + 2);
  *(int*)screenshot_address = 0;

  uint32_t game_context_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x8B\x0D\x00\x00\x00\x00\x88\x45\xEF",
    "xx????xxx");
  if (game_context_address == 0) {
    return 1;
  }

  game_context =
    *(ClientGameContext**)*(uint32_t*)(game_context_address + 2);

  uint32_t main_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x8B\x77\x58\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00",
    "xxxxx????????");
  if (main_address == 0) {
    return 1;
  }

  main =
    *(Main**)*(uint32_t*)(main_address + 5);

  uint32_t dx_renderer_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x74\x5E\x8B\x0D\x00\x00\x00\x00\x6A\x00",
    "xxxx????xx");
  if (dx_renderer_address == 0) {
    return 1;
  }

  dx_renderer =
    *(DxRenderer**)*(uint32_t*)(dx_renderer_address + 4);

  uint32_t game_renderer_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x8B\xF9\x8B\x0D\x00\x00\x00\x00\x8B\x01\x8B\x40\x38",
    "xxxx????xxxxx");
  if (game_renderer_address == 0) {
    return 1;
  }

  game_renderer =
    *(GameRenderer**)*(uint32_t*)(game_renderer_address + 4);

  uint32_t world_render_settings_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\xA3\x00\x00\x00\x00\x8A\x80\x1C\x01\x00\x00\x33\xC9",
    "x????xxxxxxxx");
  if (world_render_settings_address == 0) {
    return 1;
  }

  WorldRenderSettings* world_render_settings =
    *(WorldRenderSettings**)*(uint32_t*)(world_render_settings_address + 1);

  uint32_t camera_manager_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x74\x6D\x8B\x0D\x00\x00\x00\x00\x6A\x00",
    "xxxx????xx");
  if (camera_manager_address == 0) {
    return 1;
  }

  camera_manager =
    *(CameraManager**)*(uint32_t*)(camera_manager_address + 4);

  uint32_t client_settings_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\xA3\x00\x00\x00\x00\x80\xB8\xA4\x00\x00\x00\x00\x75\x36",
    "x????xxxxxxxxx");
  if (camera_manager_address == 0) {
    return 1;
  }

  fb::ClientSettings* client_settings =
    *(fb::ClientSettings**)*(uint32_t*)(client_settings_address + 1);

  uint32_t client_game_world_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x83\xEC\x38\xA1\x00\x00\x00\x00\x56\x57\x8B\xF9",
    "xxxx????xxxx");
  if (client_game_world_address == 0) {
    return 1;
  }

  client_game_world =
    *(GameWorld**)*(uint32_t*)(client_game_world_address + 4);

  uint32_t get_firing_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x83\xC4\x08\xA3\x00\x00\x00\x00",
    "x????xx????xxxx????");
  if (get_firing_address == 0) {
    return 1;
  }
  getWeaponFiring =
    (GetWeaponFiring)utils::GetAbsoluteAddress(get_firing_address);

  uint32_t send_spotting_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\xE8\x00\x00\x00\x00\x8D\x45\xA0\x89\x45\x94",
    "x????xxxxxx");
  if (send_spotting_address == 0) {
    return 1;
  }
  SendClientSpottingMessage sendClientSpottingMessage =
    (SendClientSpottingMessage)utils::GetAbsoluteAddress(send_spotting_address);

  hook = new utils::VtableHook(main->client->input_node->mouse);
  hook->HookMethod(Update, 3);

  swapchain_hook = new utils::VtableHook(dx_renderer->screen->swapchain);
  swapchain_hook->HookMethod(PresentHook, 8);

  while (active_thread) {
    ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
    if (local_player == nullptr) {
      Sleep(50);
      continue;
    }

    client_settings->fairfight_disabled = 1;

    // unlock everything
    *(int*)((DWORD)(local_player)+0x970) = 0;

    ClientSoldierEntity* local_soldier_entity = local_player->m_soldier.getData();

    if (local_soldier_entity == nullptr) {
      Sleep(50);
      continue;
    }

    //auto weapons = (fb::ClientSoldierWeaponsComponent*)local_soldier_entity->components->GetFirstComponentOfType(fb::ClientSoldierWeaponsComponent::CLASS_ID, fb::ClientSoldierWeaponsComponent::CLASS_ID);
    //auto weapon = weapons->GetActiveSoldierWeapon();
    //if (weapon && weapon->authorative_aiming && weapon->authorative_aiming->data) {
    //  for (size_t i = 0; i < 2; i++) {
    //    auto zoom_level = weapon->authorative_aiming->data->zoom_levels.at(i);

    //    if (!zoom_level) continue;
    //    zoom_level->sway_pitch_magnitude = 0;
    //    zoom_level->sway_yaw_magnitude = 0;
    //    zoom_level->TimePitchMultiplier = 0;
    //    zoom_level->TimeYawMultiplier = 0;
    //    zoom_level->DispersionMultiplier = 0;
    //    zoom_level->RecoilMultiplier = 0;
    //    zoom_level->RecoilFovMultiplier = 0;
    //    zoom_level->SupportedSwayPitchMagnitude = 0;
    //    zoom_level->SupportedSwayYawMagnitude = 0;
    //    zoom_level->SuppressedSwayPitchMagnitude = 0;
    //    zoom_level->SuppressedSwayYawMagnitude = 0;
    //  }
    //}


    fb::ClientSoldierBreathControlComponent* breath =
      (fb::ClientSoldierBreathControlComponent*)local_soldier_entity->components->
        GetFirstComponentOfType(fb::ClientSoldierBreathControlComponent::CLASS_ID, fb::ClientSoldierBreathControlComponent::CLASS_ID);

    if (breath) {
      breath->breath_control_timeout_multiplier = 0;
    }

    if (world_render_settings) {
      world_render_settings->distance_fog = 0;
      world_render_settings->distance_fog_cloud = 0;
      world_render_settings->sun_flare = 0;
      world_render_settings->sun_chrona = 0;
    }

    auto players = game_context->client_player_manager_->getPlayers();
    for (int i = 0; i < players->size(); i++) {
      ClientPlayer *player = players->at(i);

      if (player == nullptr) {
        continue;
      }

      if (player->team_id == 0 || player->team_id == local_player->team_id) continue;

      ClientSoldierEntity* soldier_entity = player->m_soldier.getData();

      if (soldier_entity == nullptr) {
        continue;
      }

      ClientSpottingTargetComponent* spot =
        (ClientSpottingTargetComponent*)soldier_entity->components->
        GetFirstComponentOfType(ClientSpottingTargetComponent::CLASS_ID, ClientSpottingTargetComponent::CLASS_ID);
      if (spot == nullptr) {
        continue;
      }
      spot->spot_type = SpotType::Active;
    }

    WeaponFiring* weapon_firing = getWeaponFiring(local_player, 0);

    if (weapon_firing == nullptr ||
      weapon_firing->weapon_firing_data == nullptr ||
      weapon_firing->weapon_firing_data->primary_fire == nullptr) {
      Sleep(50);
      continue;
    }

    if (weapon_firing->weapon_firing_data->primary_fire->shot_config_data.numberOfBulletsPerShell == 1) {
      weapon_firing->weapon_firing_data->primary_fire->shot_config_data.numberOfBulletsPerShell += 1;
    }

    if (weapon_firing->weapon_firing_data->primary_fire->shot_config_data.numberOfBulletsPerShell == 3) {
      weapon_firing->weapon_firing_data->primary_fire->shot_config_data.numberOfBulletsPerShell += 1;
    }

    if (local_player != nullptr && local_player->vehicle) {
      char* name = local_player->vehicle->GetPhysiscsEntity()->data->asset->name.chars;
      if (strstr(name, "Z11") || strstr(name, "AH6")) {
        weapon_firing->weapon_firing_data->primary_fire->shot_config_data.numberOfBulletsPerShell = 30;
      }
    }

    if (GetAsyncKeyState(0x51)) { // Q
      ClientSpottingComponent* spotting = (ClientSpottingComponent*)local_soldier_entity->components->GetFirstComponentOfType(ClientSpottingComponent::CLASS_ID, ClientSpottingComponent::CLASS_ID);
      eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>* soldiers = new eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>;

      spotting->spotting_data->coolDownAllowedSpotsWithinHistory = 300;
      spotting->spotting_data->RequireLineOfSight = false;

      auto players = game_context->client_player_manager_->getPlayers();
      for (int i = 0; i < players->size(); i++) {
        if (soldiers->size() == 8) {
          sendClientSpottingMessage(spotting, local_player, SpotType::Active, soldiers, 0);
          delete soldiers;
          soldiers = new eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>;
        }
        ClientPlayer *player = players->at(i);

        if (player == nullptr) {
          continue;
        }

        if (player->team_id == 0 || player->team_id == local_player->team_id) continue;

        ClientSoldierEntity* soldier_entity = player->m_soldier.getData();

        if (soldier_entity == nullptr) {
          continue;
        }

        soldiers->push_back(player->m_soldier);
      }

      if (soldiers && soldiers->size() > 0) {
        sendClientSpottingMessage(spotting, local_player, SpotType::Active, soldiers, 0);
      }

      if (soldiers) delete soldiers;
    }

    Sleep(10);
  }

  return 1;
}

int WINAPI DllMain(HINSTANCE instance, DWORD reason, PVOID reserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    CreateThread(nullptr, 0, rec_thread, 0, 0, nullptr);
  }
  else if (reason == DLL_PROCESS_DETACH) {
    active_thread = false;
    if (hook) delete hook;
    if (swapchain_hook) delete swapchain_hook;
    Sleep(2000);
  }
  return 1;
}