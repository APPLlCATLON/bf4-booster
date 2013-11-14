class ClientGameContext;
class ClientPlayerManager;
class ClientPlayer;

class ClientGameContext {
 public:
  char _0x0000[48];
  ClientPlayerManager* client_player_manager_; //0x0030
};

class ClientPlayerManager {
 public:
  virtual void function();
  virtual eastl::vector<ClientPlayer*>* getPlayers();
  virtual eastl::vector<ClientPlayer*>* getSpectators();
  char _0x0004[676];
  ClientPlayer* local_player_; //0x02a8
  ClientPlayer** m_idToPlayerMap;
};

class ClientSoldierEntity {
};

class ClientWeapon {
  public:
  char _0x0000[0x24E4];
  ClientWeapon* weapon; //0x24E4 
};

class ClientSoldierWeapon {
  public:
    char _0x0000[0x24E4];
  ClientWeapon* weapon; //0x24E4 
};

class ClientSoldierWeaponsComponent {
public:
    char _0x0000[0x498];
  ClientSoldierWeapon* weapons; //0x498 
};

class FiringFunctionData {
 public:
  char _0x0000[0xA4];
  int bullets_per_shell;
  char _0x00A8[104];
  float heat_per_bullet; //0x0110 
};

class WeaponFiringData {
 public:
  char _0x0000[0x8];
  FiringFunctionData* primary_fire;
};

class WeaponFiring {
 public:
  char _0x0000[0x94];
  WeaponFiringData* weapon_firing_data;
};

class WeaponSoldierEntity {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void* getWeaponSway(); //
  virtual WeaponFiring* getCurrentWeaponFiring();
  virtual WeaponFiringData* getCurrentWeaponFiringData();
};


class ClientSpottingTargetComponent {
 public:
  char _0x0000[0x28];
  int spot_type; 
};

class ClientPlayer {
 public:
  virtual void Function0();
  virtual ClientSoldierEntity* GetCharacterEntity();

  char _0x0000[0x97C];
  fb::WeakPtr<ClientSoldierEntity> m_soldier;
};
