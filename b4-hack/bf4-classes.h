class ClientGameContext;
class ClientPlayerManager;
class ClientPlayer;
class CharacterPhysicsEntity;
class OnlineManager;
class ClientGameView;
class ClientSoldierEntity;
class ComponentCollection;
class Client;

namespace fb {
  class String {
   public:
    char* chars;
  };
  class DataContainer {
    virtual void GetType();
    virtual void Function1();

    uint16_t ref;
    uint16_t flags;
  };
};

struct Vector3 {
 public:
  float x;
  float y;
  float z;

  float GetMagnitude() {
    return sqrtf(x * x + y * y + z * z);
  }
};

class Asset : fb::DataContainer {
 public:
  fb::String name;
};

class PhysicsEntityData {
public:
  DWORD N0129C30A; //0x0000 
  char _0x0004[8];
  Asset* asset; //0x000C 
  char _0x0010[64];
};//Size=0x0050

class PhysicsEntity {
 public:
  char _0x0000[136];
  PhysicsEntityData* data; //0x0088 
  char _0x008C[20];

};//Size=0x00A0

class ClientVehicleEntity {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //
  virtual void Function10(); //
  virtual void Function11(); //
  virtual void Function12(); //
  virtual void Function13(); //
  virtual void Function14(); //
  virtual void Function15(); //
  virtual void Function16(); //
  virtual void Function17(); //
  virtual void Function18(); //
  virtual void Function19(); //
  virtual void Function20(); //
  virtual void Function21(); //
  virtual void Function22(); //
  virtual void Function23(); //
  virtual void Function24(); //
  virtual void Function25(); //
  virtual void Function26(); //
  virtual void Function27(); //
  virtual void Function28(); //
  virtual void Function29(); //
  virtual void Function30(); //
  virtual void Function31(); //
  virtual void Function32(); //
  virtual void Function33(); //
  virtual void Function34(); //
  virtual void Function35(); //
  virtual void Function36(); //
  virtual void Function37(); //
  virtual void Function38(); //
  virtual void Function39(); //
  virtual void Function40(); //
  virtual void Function41(); //
  virtual void Function42(); //
  virtual void Function43(); //
  virtual void Function44(); //
  virtual void Function45(); //
  virtual void Function46(); //
  virtual void Function47(); //
  virtual void Function48(); //
  virtual void Function49(); //
  virtual void Function50(); //
  virtual void Function51(); //
  virtual void Function52(); //
  virtual void Function53(); //
  virtual void Function54(); //
  virtual void Function55(); //
  virtual void Function56(); //
  virtual void Function57(); //
  virtual void Function58(); //
  virtual void Function59(); //
  virtual PhysicsEntity* GetPhysiscsEntity(); //physics
  virtual Vector3* GetVelocity(); //velocity
  virtual void Function62(); //
  virtual void Function63(); //
  virtual void Function64(); //
  virtual void Function65(); //
  virtual void Function66(); //
  virtual void Function67(); //
  virtual void Function68(); //
  virtual void Function69(); //
  virtual void Function70(); //
  virtual void Function71(); //
  virtual void Function72(); //
  virtual void Function73(); //
  virtual void Function74(); //

  char _0x0004[376];
  void* physics_entity; //0x017C 
  char _0x0180[256];
  void* chassis; //0x0280 
  char _0x0284[92];

};//Size=0x02E0


enum InputConceptIdentifiers {
  ConceptMoveFB = 0x0,
  ConceptMoveForward = 0x2,
  ConceptMoveBackward = 0x3,
  ConceptCrawl =  0x11,
  ConceptBrake =  0x3A
};

class Main {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[68];
  Client* client; //0x0048 
};//Size=0x004C

class InputCache {
 public:
  char _0x0000[4];
  float input_buffer[223]; //0x0004 
  char _0x007F[1];
};//Size=0x0080

class Keyboard {
};
class Mouse {
};

class BorderInputNode {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  InputCache* input_cache; //0x0004 
  char _0x0008[52];
  Keyboard* keyboard; //0x003C 
  Mouse* mouse; //0x0040 
};

class Client {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[32];
  ClientPlayerManager* player_manager; //0x0024 
  void* destruction_manager; //0x0028 
  ClientGameView* game_view; //0x002C 
  void* file_system; //0x0030 
  void* game_time; //0x0034 
  BorderInputNode* input_node; //0x0038 

};//Size=0x003C

class Screen {
 public:
  char _0x0000[40];
  __int32 width; //0x0028 
  __int32 height; //0x002C 
  char _0x0030[120];
  void* swapchain; //0x00A8 

};//Size=0x00AC

class DxRenderer {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[28];
  Screen* screen; //0x0020 
  char _0x0024[116];
  void* device; //0x0098 
  void* device_context; //0x009C 
  char _0x00A0[960];
}; // 0x460 (1120)

class ClientGameContext {
 public:
  char _0x0000[48];
  ClientPlayerManager* client_player_manager_; //0x0030
  OnlineManager* online_manager_;
  ClientGameView* client_game_view_;
};

class ClientGameView {
public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //
  virtual void Function10(); //
  virtual void Function11(); //
  virtual void Function12(); //
  virtual void Function13(); //
  virtual void Function14(); //
  virtual void Function15(); //
  virtual void Function16(); //
  virtual void Function17(); //
  virtual void Function18(); //
  virtual void Function19(); //
  virtual void Function20(); //
  virtual void setActiveCamera(int id); //
};

class Camera {
};

class CameraManager {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual Camera* getActiveCamera(int unknown); //
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

class Component {
};

class GameEntity {
};

class ClientSoldierEntity {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[4];
  int flags; //0x0008 
  char _0x000C[16];
  ComponentCollection* components; //0x001C 
  char _0x0020[220];
  CharacterPhysicsEntity* physics_entity;
  char _0x00FC; //0x00FC
  bool has_physiscs_entity; //0x00FD
  char _0x00FE[734];
  bool was_sprinting; //0x03DC 
  bool is_occluded; //0x03DD 
}; //size 0x0490 (1168)


class ClientSoldierEmoteComponent {
 public:
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[24];
  ClientSoldierEntity* soldier; //0x001C 
  void* state; //0x0020 
  void* emote_manager; //0x0024 
  char _0x0028[68];
  BYTE N00B27650; //0x006C 
  BYTE saying_something; //0x006D 
  char _0x006E[18];
  BYTE last_speak; //0x0080 
  char _0x0081[3];


  static const int CLASS_ID = 304;
};//size 0x0084 (132)

class ComponentCollection {
 public:
  GameEntity *owner;
  char playerCount;
  char totalCount;
  char offsetCount;

  struct ComponentCollectionEntry {
    short id;
    short sub_id;
    int unknown_1;
    int unknown_2;
    Component* component;
  };

  Component* GetFirstComponentOfType(int class_id) {
    for (int i = 0; i < playerCount; i++) {
      ComponentCollectionEntry* entry = (ComponentCollectionEntry*)((DWORD)this + 0x10 + 0x10 * i); 
      if (entry->id == class_id && entry->component != nullptr) {
        return entry->component;
      }
    }
    return nullptr;
  }
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

class SpottingComponentData {
 public:
  char _0x0000[96];
  float spotting_fov; //0x0060 
  float team_order_fov; //0x0064 
  float spotting_distance; //0x0068 
  float passive_spotting_time_interval; //0x006C 
  float time_required_to_passive_spot; //0x0070 
  float order_need_ammo_percentage; //0x0074 
  float order_heal_percentage; //0x0078 
  float order_repair_percentage; //0x007C 
  float pickup_order_distance; //0x0080 
  float heal_order_distance; //0x0084 
  float ammo_order_distance; //0x0088 
  float repair_order_distance; //0x008C 
  float cool_down_history_time; //0x0090 
  int coolDownAllowedSpotsWithinHistory; //0x0094 
  float auto_spotting_time_interval; //0x0098 
  float active_spotting_target_time_multiplier; //0x009C 
  bool OnlyAllowedToHaveOneSpottedPlayer ; //0x00A0 
  bool RequireLineOfSight ; //0x00A1 
  bool ActiveSpottingEnabled ; //0x00A2 
  bool PassiveSpottingEnabled ; //0x00A3 
  bool AutoSpottingEnabled ; //0x00A4 
  char _0x00A5[11];

};//Size=0x00B0

class ClientSpottingComponent {
 public:
  char _0x0000[40];
  SpottingComponentData* spotting_data; //0x0028 
  char _0x002C[1744];
  static const int CLASS_ID = 406;
};//size 0x06FC (1788)

enum SpotType {
  None    = 0,
  Active  = 1,
  Passive = 2,
  Radar   = 3
};

class ClientSpottingTargetComponent {
 public:
  char _0x0000[0x28];
  SpotType spot_type; 


  static const int CLASS_ID = 348;
};

class hkpCharacterContext {
};

struct hkVector4 {
  float x;
  float y;
  float z;
  float w;
};

class hkpCharacterInput {
 public:
  char _0x0000[64];
  int supported_surface; //0x0040 
  char _0x0044[108];
  hkVector4 m_characterGravity;
  unsigned int m_userData;
};

class hkpCharacterOutput {
 public:
  hkVector4 velocity;
};

class hkpCharacterProxy {
};

class CharacterPhysicsEntityContext {
};

class hkpCharacterState {
  virtual void Function0(); //
  virtual void Function1(); //
  virtual void Function2(); //
  virtual void Function3(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void update(); // 6
  virtual void Function7(); //
  virtual void Function8(); //
};

class hkpCharacterStateManager {
 public:
  virtual void Function0(); //

  char _0x0004[0x4];
  hkpCharacterState* registered_state[11];
};

class hkpSimpleShapePhantom {
};

enum CharacterPoseType {
  Stand = 0x0,
  Crouch = 0x1,
  Prone = 0x2
};

enum CharacterStateType {
  OnGround = 0,
  Jumping =  1,
  InAir   = 2,
  Falling = 3,
  Parachute = 4,
  Swimming  = 5,
  Climbing = 6,
  AnimationControlled = 7,
  Sliding = 8
};

class CharacterSprintData {
}; //size 0x0018 (24)

struct LookConstraintsData {
  float m_minLookYaw;
  float m_maxLookYaw;
  float m_minLookPitch;
  float m_maxLookPitch;
};

enum CharacterPoseCollisionType {
  Capsule = 0x0,
  Pencil = 0x1
};

class CharacterPoseData : fb::DataContainer {
  char _0x000C[60];
  LookConstraintsData look_constraints;
  CharacterPoseType pose_type;
  CharacterPoseCollisionType collision_type;
}; //size 0x0060 (96)

struct SpeedModifierData {
  float m_forwardConstant;
  float m_backwardConstant;
  float m_leftConstant;
  float m_rightConstant;
};

class CharacterStatePoseInfo : fb::DataContainer {
 public:
  CharacterPoseType type;
  float velocity;
  float acceleration_gain;
  float deceleration_gain;
  float sprint_gain;
  float sprint_multiplier;
  SpeedModifierData modifer_data;
  float unknown;
}; //size 0x0034 (52)

class CharacterStateData : fb::DataContainer {
 public:
  fb::RefArray<CharacterStatePoseInfo> poses;
}; //size 0x000C (12)

class OnGroundStateData : public CharacterStateData {
 public:
  float jump_delay;
  float jump_stamina_delay;
  float allowed_distance_from_ground;
  uint16_t unknown;
};

class JumpStateData : CharacterStateData {
 public:
  float jump_height;
  float jump_effect_size;
};

class InAirStateData : CharacterStateData {
  float free_fall_velocity;
};

class FallingStateData : CharacterStateData {

};

class ParachuteStateData : CharacterStateData {
  float m_deployTime;
  float m_terminalVelocity;
  float m_forwardDragCoefficient;
  float m_angleOfAttack;
  float m_bankOffset;
  float m_throttleOffset;
  float m_brakeOffset;
  float m_maxRollVelocity;
  float m_maxPitchVelocity;
  float m_maxYawVelocity;
};  //size 0x0034 (52)

class SwimmingStateData : CharacterStateData {
  float m_bodyUnderWater;
};

class ClimbingStateData : CharacterStateData {
  float m_lateralInputScale;
  float m_downAngleLimit;
  float m_dropOffAngle;
  float m_attractionVelocity;
  float m_pushAwayVelocity;
  float m_climbHeightOffset;
  float m_climbOffVerticalDistance;
  float m_climbOffVerticalTime;
  float m_climbOffHorizontalDistance;
  float m_climbOffHorizontalTime;
};

class AnimationControlledStateData : CharacterStateData {
  float m_upNormalTolerance;
};

class SlidingStateData : CharacterStateData {
  float m_horizontalInputScale;
  float m_gravityScale;
};

class CharacterPhysicsData : fb::DataContainer  {
 public:
  fb::String* asset_name; //0x0008 
  fb::RefArray<CharacterPoseData> poses; //0x000C 
  fb::RefArray<CharacterStateData> states; //0x0010 
  __int32 default_state_type; //0x0014 
  CharacterSprintData* sprint_data; //0x0018 
  char _0x001C[4];
  __int32 pushable_object_weight; //0x0020 
  float mass; //0x0024 
  float max_ascend_angle; //0x0028 
  float radius; //0x002C 
  float water_depth_limit; //0x0030 
  float input_acceleration; //0x0034 
  float ladder_accept_angle; //0x0038 
  float ladder_accept_angle_pitch; //0x003C 
  float jump_penalty_time; //0x0040 
  float jump_penalty_factor; //0x0044 
  char _0x0048[12];

}; //size 0x0054 (84)

class hkpRigidBody {
};

class CharacterPhysicsEntity {
 public:
  virtual void getType(); //
  virtual void deconstructor(); //
  virtual void addToWorld(); //
  virtual void removeFromWorld(); //
  virtual void Function4(); //
  virtual void Function5(); //
  virtual void Function6(); //
  virtual void Function7(); //
  virtual void Function8(); //
  virtual void Function9(); //

  char _0x0004[76];
  hkpCharacterProxy* character_proxy; //0x0050 
  CharacterPhysicsEntityContext* physics_entity_context; //0x0054 
  hkpCharacterStateManager* hkp_character_state_manager; //0x0058 
  hkpSimpleShapePhantom* phantom; //0x005C 
  char _0x0060[12];
  int current_pose; //0x006C 
  int next_pose; //0x0070 
  float pose_transition_time; //0x0074 
  char _0x0078[44];
  CharacterPhysicsData* physics_data; //0x00A4
  fb::RefArray<CharacterPoseData> poses;
  char _0x00A8[32];
  hkpRigidBody* rigib_body_proxy; //0x00CC 
  char _0x00D0[320];
}; //size 0x0210 (528)

class ClientPlayer {
 public:
  virtual void Function0();
  virtual ClientSoldierEntity* GetCharacterEntity();

  char _0x0004[2288];
  int team_id; //0x08F4 
  char _0x08F8[136];
  fb::WeakPtr<ClientSoldierEntity> m_soldier;
  char _0x0984[4];
  ClientVehicleEntity* vehicle;
  char _0x098C[12];
  void* input; //0x0998 
  void* input_state; //0x099C 
};
