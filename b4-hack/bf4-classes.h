class ClientGameContext;
class ClientPlayerManager;
class ClientPlayer;
class CharacterPhysicsEntity;

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

  char _0x0004[0xF8];
  CharacterPhysicsEntity* physics_entity;
  char _0x00FC; //0x00FC 
  bool has_physiscs_entity; //0x00FD 
}; //size 0x0490 (1168)

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

class hkpCharacterProxy {
};

class CharacterPhysicsEntityContext {
};

class hkpCharacterStateManager {
};

class hkpSimpleShapePhantom {
};

namespace fb {
  class String {
    char* chars;
  };
  class DataContainer {
    virtual void GetType();
    virtual void Function1();

    uint16_t ref;
    uint16_t flags;
  };
};

enum CharacterPoseType {
  Stand = 0x0,
  Crouch = 0x1,
  Prone = 0x2
};

enum CharacterStateType {
  OnGround = 0x0,
  Jumping =  0x1,
  InAir   = 0x2,
  Falling = 0x3,
  Parachute = 0x4,
  Swimming  = 0x5,
  Climbing = 0x6,
  AnimationControlled = 0x7,
  Sliding = 0x8
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

  char _0x0000[0x97C];
  fb::WeakPtr<ClientSoldierEntity> m_soldier;
};
