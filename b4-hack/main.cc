// Copyright 2013 Karl Skomski - GPL v3

#include "utils\vmthooks.h"
#include "utils\utils.h"
#include "fb\core\WeakPtr.h"
#include "fb\core\RefArray.h"
#include "eastl\eastl.h"
#include "bf4-classes.h"

HANDLE thread = nullptr;

bool active_thread = true;

typedef ClientSpottingTargetComponent* ( __thiscall* GetClientSpottingTargetComponent )(void*, int);
typedef WeaponFiring* ( __cdecl* GetWeaponFiring )(ClientPlayer*, int);

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

  ClientGameContext* game_context =
    *(ClientGameContext**)*(uint32_t*)(game_context_address + 2);

  uint32_t get_spotting_address =
    (uint32_t)utils::FindPattern(
        "bf4_x86.exe",
        (unsigned char*)"\xE8\x00\x00\x00\x00\x85\xDB\x74\x7C",
        "x????xxxx");
  if (get_spotting_address == 0) {
    return 1;
  }
  GetClientSpottingTargetComponent getClientSpottingTargetComponent =
    (GetClientSpottingTargetComponent)utils::GetAbsoluteAddress(get_spotting_address);

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

  while (active_thread) {
    auto players = game_context->client_player_manager_->getPlayers();  
    for(  int i = 0; i < players->size() ; i++ ) {
      ClientPlayer *player = players->at(i);

      if (player == nullptr) {
        continue;
      }

      ClientSoldierEntity* soldier_entity = player->m_soldier.getData();

      if (soldier_entity == nullptr) {
        continue;
      }

      ClientSpottingTargetComponent* spot = getClientSpottingTargetComponent(soldier_entity, 0);
      if (spot == nullptr) {
        continue;
      }
      spot->spot_type = 1;
    }

    ClientPlayer* local_player = game_context->client_player_manager_->local_player_;
    if (local_player == nullptr) {
      Sleep(50);
      continue;
    }

    // unlock everything
    *(int*)((DWORD)(local_player) + 0x970) = 0;

    WeaponFiring* weapon_firing = getWeaponFiring(local_player, 0);

    if (weapon_firing == nullptr ||
        weapon_firing->weapon_firing_data == nullptr ||
        weapon_firing->weapon_firing_data->primary_fire == nullptr) {
      Sleep(50);
      continue;
    }

    if (weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell == 1) {
      weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell += 1;
    }

    if (weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell == 3) {
      weapon_firing->weapon_firing_data->primary_fire->bullets_per_shell += 1;
    }
    
    ClientSoldierEntity* soldier_entity = local_player->m_soldier.getData();

    if (soldier_entity == nullptr ||
        soldier_entity->physics_entity == nullptr) {
      continue;
    }

    soldier_entity->physics_entity->physics_data->water_depth_limit = 10;
    JumpStateData* jump_data =  (JumpStateData*)soldier_entity->physics_entity->physics_data->states.at(CharacterStateType::Jumping);
    if (GetAsyncKeyState(0x54)) { // T
      jump_data->jump_height = jump_data->jump_height == 50 ? 0.600 : 50;
    }
    OnGroundStateData* ground_data =  (OnGroundStateData*)soldier_entity->physics_entity->physics_data->states.at(CharacterStateType::OnGround);
    if (GetAsyncKeyState(0x59)) { // Y
      auto stand = ground_data->poses.at(CharacterPoseType::Stand);
      stand->velocity = stand->velocity == 4 ? 6 : 4;
    }
    Sleep(200);
  }

  return 1;
}

int WINAPI DllMain(HINSTANCE instance, DWORD reason, PVOID reserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    CreateThread(nullptr, 0, rec_thread, 0, 0, nullptr);
  } else if (reason == DLL_PROCESS_DETACH) {
    active_thread = false;
    Sleep(200);
  }
  return 1;
}