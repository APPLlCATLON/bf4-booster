// Copyright 2013 Karl Skomski - GPL v3

#include "utils\vmthooks.h"
#include "utils\utils.h"
#include "fb\core\WeakPtr.h"
#include "fb\core\RefArray.h"
#include "eastl\eastl.h"
#include "bf4-classes.h"

HANDLE thread = nullptr;
bool active_thread = true;

typedef WeaponFiring* ( __cdecl* GetWeaponFiring )(ClientPlayer*, int);
typedef void ( __thiscall* SendClientSpottingMessage )(ClientSpottingComponent*, ClientPlayer*, SpotType type, eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>*, ClientSoldierEntity* unknown);

utils::VtableHook* hook = nullptr;
ClientGameContext* game_context = nullptr;
Main* main = nullptr;

void __fastcall Update(Main *thisptr, void* edx, float delta) {
  ClientPlayer* local_player = game_context->client_player_manager_->local_player_;

  typedef void ( __thiscall* OrgMethod )(void*, float);
  hook->GetMethod<OrgMethod>(3)(thisptr, delta);

  if (local_player != nullptr && local_player->vehicle) {
    char* name = local_player->vehicle->GetPhysiscsEntity()->data->asset->name.chars;
    if (strstr(name, "F35") || strstr(name, "A-10") || strstr(name, "SU-25") ||
        strstr(name, "fantan") || strstr(name, "J-20")) {
    float speed = local_player->vehicle->GetVelocity()->GetMagnitude()* 3.6f;

    if (speed <= 310 && speed > 20) {
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveFB] = 1.0f;
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveForward] = 1.0f;
    } else if (speed >= 315 && speed > 20) {
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveFB]  = -1.0f;
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptMoveBackward]  = 1.0f;
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptCrawl] = 1.0f;
      main->client->input_node->input_cache->input_buffer[InputConceptIdentifiers::ConceptBrake] = 1.0f;
    }
    }
  }
}

static float buffer[223] = {0};

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

  DxRenderer* dx_renderer =
    *(DxRenderer**)*(uint32_t*)(dx_renderer_address + 4 );

  uint32_t camera_manager_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\x74\x6D\x8B\x0D\x00\x00\x00\x00\x6A\x00",
    "xxxx????xx");
  if (camera_manager_address == 0) {
    return 1;
  }

  CameraManager* camera_manager =
    *(CameraManager**)*(uint32_t*)(camera_manager_address + 4);

  uint32_t get_firing_address =
    (uint32_t)utils::FindPattern(
    "bf4_x86.exe",
    (unsigned char*)"\xE8\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x83\xC4\x08\xA3\x00\x00\x00\x00",
    "x????xx????xxxx????");
  if (get_firing_address == 0) {
    return 1;
  }
  GetWeaponFiring getWeaponFiring =
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

  hook = new utils::VtableHook(main->client->input_node->keyboard);
  hook->HookMethod(Update, 3);

  while (active_thread) {
    ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
    if (local_player == nullptr) {
      Sleep(50);
      continue;
    }

     // unlock everything
    *(int*)((DWORD)(local_player) + 0x970) = 0;

    ClientSoldierEntity* local_soldier_entity = local_player->m_soldier.getData();

    if (local_soldier_entity == nullptr) {
      continue;
    }

    auto players = game_context->client_player_manager_->getPlayers();
    for(int i = 0; i < players->size() ; i++ ) {
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
        GetFirstComponentOfType(ClientSpottingTargetComponent::CLASS_ID);
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

    if (weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell == 1) {
      weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell += 50;
    }

    if (weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell == 3) {
      weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell += 1;
    }

    if (GetAsyncKeyState(0x51)) { // Q
      ClientSpottingComponent* spotting = (ClientSpottingComponent*)local_soldier_entity->components->GetFirstComponentOfType(ClientSpottingComponent::CLASS_ID);
      eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>* soldiers = new eastl::fixed_vector<fb::WeakPtr<ClientSoldierEntity>, 8>;

      spotting->spotting_data->coolDownAllowedSpotsWithinHistory = 300;
      spotting->spotting_data->RequireLineOfSight = false;

      auto players = game_context->client_player_manager_->getPlayers();
      for(int i = 0; i < players->size() ; i++ ) {
          if (soldiers && soldiers->size() == 8) {
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

        ClientSpottingTargetComponent* spot = 
          (ClientSpottingTargetComponent*)soldier_entity->components->
          GetFirstComponentOfType(ClientSpottingTargetComponent::CLASS_ID);
        if (spot == nullptr) {
          continue;
        }
        spot->spot_type = SpotType::Active;
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
  } else if (reason == DLL_PROCESS_DETACH) {
    active_thread = false;
    if (hook) delete hook;
    Sleep(2000);
  }
  return 1;
}