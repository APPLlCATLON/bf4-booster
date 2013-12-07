#include <DirectXMath.h>

class ID3D11Device;
class ID3D11DeviceContext;
class D3DXMATRIX;

class ClientGameContext;
class ClientPlayerManager;
class ClientPlayer;
class CharacterPhysicsEntity;
class OnlineManager;
class ClientGameView;
class ClientSoldierEntity;
class ComponentCollection;
class Client;
class WeaponFiring;
class TypeInfo;

class UpdatePoseResultData {
 public:

  enum BONES {
    BONE_HEAD = 104,
    BONE_NOSETIP = 98,
    BONE_NECK = 142,
    BONE_SPINE2 = 7,
    BONE_SPINE1 = 6,
    BONE_SPINE = 5,
    BONE_LEFTSHOULDER = 9,
    BONE_RIGHTSHOULDER = 109,
    BONE_LEFTELBOWROLL = 11,
    BONE_RIGHTELBOWROLL = 111,
    BONE_LEFTHAND = 15,
    BONE_RIGHTHAND = 115,
    BONE_LEFTKNEEROLL = 188,
    BONE_RIGHTKNEEROLL = 197,
    BONE_LEFTFOOT = 184,
    BONE_RIGHTFOOT = 198
  };

  class QuatTransform {
   public:
    DirectX::XMVECTOR trans_and_scale; // 0x0000
    DirectX::XMVECTOR rotation;  // 0x0010
  }; // Size 0x0020

  QuatTransform* local_transforms;  // 0x0000
  QuatTransform* world_transforms; // 0x0004
  QuatTransform* render_transforms; // 0x008
  QuatTransform* interpolated_local_transforms; // 0x00C
  QuatTransform* interpolated_world_transforms; // 0x0010
  QuatTransform* active_world_transforms; // 0x0014
  QuatTransform* active_local_transforms; // 0x0018
  int slot; // 0x001C
  int reader_index;  // 0x0020
  bool valid_transforms; // 0x0024
  BYTE pose_update_enabled; // 0x0025
  BYTE pose_needed; // 0x0026
  BYTE pad27[0x01]; // 0x0027
};

class AnimationSkeleton {
 public:
  void* skeletonAsset;
  int bone_count;
};

class ClientControllableEntity {
 public:
  virtual TypeInfo* getType();
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
  virtual void GetTransform(DirectX::XMMATRIX* mTransform); //

  char _0x0004[128];
  int team_id; //0x0084
};

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
  class EntityBusPeer : public DataContainer
  {
  public:
  };//size 0x0004 (4)
  class Component : public EntityBusPeer
  {
  public:
    char pad_0x0004[0x000C];//
  };//size 0x0010 (16)
  class GameComponent
    :public Component
  {
  public:
    char pad_0x0010[0x0008];//
  };//size 0x0018 (24)
  class ClientGameComponent
    :public GameComponent
  {
  public:
    char pad_0x0018[0x0004];//
  };//size 0x001C (28)
  class ClientBoneCollisionComponent
    : public ClientGameComponent
  {
  public:
    void* bone_collision_component_data; //0x0000 
    UpdatePoseResultData pose_result_data;
    AnimationSkeleton* skeleton; //0x002C 
    void* bone_collision_transforms; //0x0030 

    static const int CLASS_ID = 379;
  };//size 0x01F8 (504)
  class ClientBoneComponent : public ClientGameComponent {
    public:
  };//size 0x001C (28)
  class ClientWeaponComponent : public ClientBoneComponent {
  public:
    char pad_0x001C[0x0068];//

    static const int CLASS_ID = 340;
  };//size 0x0084 (132)
  class Entity : public EntityBusPeer
  {
  public:
    char pad_0x0004[0x000C];//
  };//size 0x0010 (16)
  class SpatialEntity : public Entity
  {
  public:
    char pad_0x0010[0x0004];//
  };//size 0x0014 (20)
  class ComponentEntity : public SpatialEntity
  {
  public:
    char pad_0x0014[0x000C];//
  };//size 0x0020 (32)
  class GameComponentEntity : public ComponentEntity
  {
  public:
    char pad_0x0020[0x0014];//
  };//size 0x0034 (52)
  class ClientGameComponentEntity : public GameComponentEntity
  {
  public:

  };//size 0x0034 (52)
  class Tool {
  public:
    char pad_0x0000[0xC];//
  };//size 0x000C (12)
  class Weapon
    :public Tool
  {
  public:
    char pad_0x000C[0x0124];//
  };//size 0x0130 (304)
  class ControllableFinder {
    public:
      char pad_0x0000[0x470];
      fb::WeakPtr<ClientControllableEntity> in_aim;
  };
  class ClientWeapon
    :public Weapon
  {
  public:
    char pad_0x0130[0xc0];//
    ControllableFinder finder;
  };//size 0x0750 (1872)
  class ZoomLevelData : public DataContainer {
   public:
    float fov; //0x0008 
    float fov_sp; //0x000C 
    void* field_of_view_transition; //0x0010 
    float look_speed_multiplier; //0x0014 
    float sprint_look_speed_multiplier; //0x0018 
    float move_speed_multiplier; //0x001C 
    float sway_pitch_magnitude; //0x0020 
    float sway_yaw_magnitude; //0x0024 
    float SupportedSwayPitchMagnitude; //0x0028 
    float SupportedSwayYawMagnitude; //0x002C 
    float SuppressedSwayPitchMagnitude; //0x0030 
    float SuppressedSwayYawMagnitude; //0x0034 
    float SuppressedSwayMinFactor; //0x0038 
    float TimePitchMultiplier; //0x003C 
    float TimeYawMultiplier; //0x0040 
    float DispersionMultiplier; //0x0044 
    float DispersionRotation; //0x0048 
    float RecoilMultiplier; //0x004C 
    float RecoilFovMultiplier; //0x0050 
    float CameraImpulseMultiplier; //0x0054 
    float StartFadeToBlackAtTime; //0x0058 
    float FadeToBlackDuration; //0x005C 
    float StartFadeFromBlackAtTime; //0x0060 
    float FadeFromBlackDuration; //0x0064 
    float ScreenExposureAreaScale; //0x0068 
    DWORD OnActivateEventType; //0x006C 
    float AttractYawStrength; //0x0070 
    float AttractPitchStrength; //0x0074 
    BYTE AllowFieldOfViewScaling; //0x0078 
    BYTE FadeToBlackInZoomTransition; //0x0079 
    BYTE UseFovSpecialisation; //0x007A 
    BYTE UseWeaponMeshZoom1p; //0x007B 
  };//Size=0x007C
  class ClientSoldierAimingSimulationData : public DataContainer {
   public:
    fb::RefArray<ZoomLevelData> zoom_levels;
  };
  class FPSAimer {
    public:
      char _0x0000[12];
      float yaw; //0x000C 
      float pitch; //0x0010
  };
  class ClientSoldierAimingSimulation {
    public:
      ClientSoldierAimingSimulationData* data; //0x0000 
      void* enviroment; //0x0004 
      FPSAimer* fps_aimer; //0x0008 

  };
  class ClientSoldierWeapon {
   public:
    char _0x0000[9272];
    BYTE breath_control_enabled; //0x2438 
    char _0x2439[155];
    ClientSoldierAimingSimulation* authorative_aiming; //0x24D4 
    char _0x24D8[12];
    ClientWeapon* weapon;
  };//size 0x2528 (9512)

  class ClientSoldierWeaponsComponent
    :public ClientGameComponent
  {
  public:
    struct ClientAnimatedSoldierWeaponHandler {
      ClientSoldierWeapon* weapon_list[7]; //0x0000 
    };

    enum WeaponSlot
    {
      M_PRIMARY = 0,
      M_SECONDARY = 1,
      M_GADGET = 2,
      M_GRENADE = 6,
      M_KNIFE = 7
    };

    char _0x0000[1144];
    ClientAnimatedSoldierWeaponHandler* weapons; //0x047C 
    char _0x0480[256];
    WeaponSlot active; //0x05B8
    WeaponSlot last_active; //0x05BC

    ClientSoldierWeapon* GetActiveSoldierWeapon() {
      if (active == 0 || active == 1 || active == 2)
        return weapons->weapon_list[active];
      else
        return nullptr;
    };

    static const int CLASS_ID = 376;
  };//size 0x0830 (2096)
  class ClientAntAnimatableComponent 
  {
  public:
    char _0x0000[0x100];
    bool had_visual_update;

    static const int CLASS_ID = 326;
  };//size 0x04F0 (1264)

  class ClientRagdollComponent {
  public:
    char _0x0000[48];
    AnimationSkeleton* skeleton; //0x0030 
    char _0x0034[24];
    UpdatePoseResultData pose_result_data; //0x004C 

    static const int CLASS_ID = 394;
  };//size 0x01A0 (416)

  struct ClientSoldierBreathControlData {
    char _0x0000[96];
    float N0059E06E; //0x0060 
    float N0059E06F; //0x0064 
    float multiplier; //0x0068 
  };

  class ClientSoldierBreathControlComponent {
   public:
     char _0x0000[8];
     ClientSoldierBreathControlData* data; //0x0008 
     char _0x000C[16];
     float breath_timer; //0x001C 
     float breath_timer_multiplier; //0x0020 
     char _0x0024[8];
     float breath_control; //0x002C 
     char _0x0030[12];
     float breath_control_timeout_multiplier; //0x003C 
     char _0x0040[8];
     BYTE flag; //0x0048 

    static const int CLASS_ID = 301;
  };//size 0x007C (124)

  class ClientSettings {
   public:
    char __0x0000[0xA4];
    byte fairfight_disabled;
  };//size 0x00D4 (212)

  class WeaponComponent {

  };

  class EntryComponent {
   public:
    class WeaponInfo {
     public:
      virtual void Function0();
      virtual void Function1();
      virtual void Function2();
      virtual void Function3();
      virtual WeaponFiring* GetWeaponFiring();
      virtual ClientWeapon* GetWeapon();
      virtual bool ActiveInStance(int stance);
      virtual WeaponComponent* GetWeaponComponent();
    };

    class FiringCallbacks {
     public:
      virtual void Function0();
      char __0x0004[0x4];
      WeaponInfo* weapon_info;
    };

    virtual int GetActiveStance();

    eastl::vector<FiringCallbacks*> weapons;
  };

  class ClientEntryComponent {
   public:
    static const int CLASS_ID = 329;
    static const int CLASS_LAST_SUB_ID = 332;
  };
  class ClientSoldierEntryComponent {
   public:
     char __0x0023[3];
    static const int CLASS_ID = 331;
  };//size 0x0180 (384)
};

class WorldRenderSettings {
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

  char _0x0004[60];
  BYTE N001BF1AC; //0x0040 
  char _0x0041[147];
  BYTE ground_light; //0x00D4 
  BYTE N001DC9DC; //0x00D5 
  BYTE N001E378F; //0x00D6 
  BYTE N001DC9DD; //0x00D7 
  BYTE N001BF186; //0x00D8 
  BYTE N001EAA62; //0x00D9 
  BYTE N001EB3E6; //0x00DA 
  BYTE complete_ground_light; //0x00DB 
  BYTE N001BF185; //0x00DC 
  BYTE N001F56AE; //0x00DD 
  BYTE N001F5C0E; //0x00DE 
  BYTE N001F56AF; //0x00DF 
  BYTE N001BF184; //0x00E0 
  BYTE N001FCF9C; //0x00E1 
  BYTE N001FD569; //0x00E2 
  BYTE next_ground_light; //0x00E3 
  BYTE shadows; //0x00E4 
  BYTE N0020B031; //0x00E5 
  BYTE N0020F6C5; //0x00E6 
  BYTE N0020B032; //0x00E7 
  BYTE N001BF182; //0x00E8 
  BYTE N002120F4; //0x00E9 
  BYTE N00212AD6; //0x00EA 
  BYTE N002120F5; //0x00EB 
  BYTE N001BF181; //0x00EC 
  BYTE N00215BBA; //0x00ED 
  BYTE N002164A2; //0x00EE 
  BYTE N00215BBB; //0x00EF 
  BYTE N001BF180; //0x00F0 
  BYTE N0023E74A; //0x00F1 
  BYTE blur_thing; //0x00F2 
  BYTE N0023E74B; //0x00F3 
  BYTE enable; //0x00F4 
  BYTE N0023E74D; //0x00F5 
  BYTE N0026F1D2; //0x00F6 
  BYTE N0023E74E; //0x00F7 
  BYTE N001BF17E; //0x00F8 
  BYTE N002F5385; //0x00F9 
  BYTE N002F5BA3; //0x00FA 
  BYTE N002F5386; //0x00FB 
  BYTE N001BF17D; //0x00FC 
  BYTE N002F9D0A; //0x00FD 
  BYTE N002FA2A8; //0x00FE 
  BYTE N002F9D0B; //0x00FF 
  BYTE N001BF17C; //0x0100 
  BYTE N003150A6; //0x0101 
  BYTE N00315847; //0x0102 
  BYTE N003150A7; //0x0103 
  BYTE N001BF17B; //0x0104 
  BYTE N0031BBEE; //0x0105 
  BYTE N0031C5B1; //0x0106 
  BYTE N0031BBEF; //0x0107 
  char _0x0108[16];
  BYTE N001BF176; //0x0118 
  BYTE N003201CA; //0x0119 
  BYTE N003209D9; //0x011A 
  BYTE N003201CB; //0x011B 
  BYTE N001BF175; //0x011C 
  BYTE N003259A1; //0x011D 
  BYTE draw_first_person; //0x011E 
  BYTE N003259A2; //0x011F 
  BYTE N001BF174; //0x0120 
  BYTE N0033825D; //0x0121 
  BYTE N0033875F; //0x0122 
  BYTE N0033825E; //0x0123 
  BYTE N001BF173; //0x0124 
  BYTE sky_box; //0x0125 
  BYTE distance_fog; //0x0126 
  BYTE distance_fog_cloud; //0x0127 
  BYTE sun_chrona; //0x0128 
  BYTE N003CC68E; //0x0129 
  BYTE N003CCDF1; //0x012A 
  BYTE N003CC68F; //0x012B 
  BYTE N001BF171; //0x012C 
  BYTE N003D6D5F; //0x012D 
  BYTE light_effect; //0x012E 
  BYTE N003D6D60; //0x012F 
  BYTE light_reflections; //0x0130 
  BYTE more_light_effect; //0x0131 
  BYTE N003DFDE5; //0x0132 
  BYTE N003DF700; //0x0133 
  BYTE N001BF16F; //0x0134 
  BYTE N003EA2BF; //0x0135 
  BYTE N003EA8DA; //0x0136 
  BYTE N003EA2C0; //0x0137 
  BYTE N001BF16E; //0x0138 
  BYTE N003FBD57; //0x0139 
  BYTE N003FC2D6; //0x013A 
  BYTE N003FBD58; //0x013B 
  char _0x013C[80];
  BYTE N001BF159; //0x018C 
  BYTE N00402AB1; //0x018D 
  BYTE N004033F7; //0x018E 
  BYTE N00402AB2; //0x018F 
  BYTE N001BF158; //0x0190 
  BYTE N0040472D; //0x0191 
  BYTE N00404C20; //0x0192 
  BYTE N0040472E; //0x0193 
  BYTE N001BF157; //0x0194 
  BYTE N00406050; //0x0195 
  BYTE N004065DE; //0x0196 
  BYTE N00406051; //0x0197 
  BYTE N001BF156; //0x0198 
  char _0x0199[167];
  BYTE N001BF12C; //0x0240 
  BYTE objects; //0x0241 
  BYTE N0039AD82; //0x0242 
  BYTE N0039A842; //0x0243 
  BYTE N001BF12B; //0x0244 
  BYTE N003A413C; //0x0245 
  BYTE sun_flare; //0x0246 
  BYTE N003A413D; //0x0247 
  BYTE N001BF12A; //0x0248 
  BYTE N003A8507; //0x0249 
  BYTE N003A8C88; //0x024A 
  BYTE N003A8508; //0x024B 
  BYTE N001BF129; //0x024C 
  BYTE N003B107B; //0x024D 
  BYTE N003B1732; //0x024E 
  BYTE N003B107C; //0x024F 
  BYTE N001BF128; //0x0250 
  BYTE N003B66AC; //0x0251 
  BYTE vegetation; //0x0252 
  BYTE N003B66AD; //0x0253 
  BYTE N001BF127; //0x0254 
  BYTE N0021D794; //0x0255 
  BYTE N0021E199; //0x0256 
  BYTE N0021D795; //0x0257 
  BYTE light_stuff; //0x0258 
  BYTE N0021D797; //0x0259 
  BYTE N0021F339; //0x025A 
  BYTE N0021D798; //0x025B 
  BYTE N001BF125; //0x025C 
  BYTE N0022F993; //0x025D 
  BYTE N0023021E; //0x025E 
  BYTE N0022F994; //0x025F 
  BYTE N001BF124; //0x0260 
  BYTE N00235A8E; //0x0261 
  BYTE N002362BC; //0x0262 
  BYTE N00235A8F; //0x0263 
  BYTE N001BF123; //0x0264 
  BYTE N0038A3EF; //0x0265 
  BYTE N0038AE9C; //0x0266 
  BYTE N0038A3F0; //0x0267 
  BYTE N001BF122; //0x0268 
  BYTE N00391F7B; //0x0269 
  BYTE N00392681; //0x026A 
  BYTE N00391F7C; //0x026B 
  BYTE N001BF121; //0x026C 
  BYTE N00410752; //0x026D 
  BYTE N00410D5D; //0x026E 
  BYTE N00410753; //0x026F 
  BYTE N001BF120; //0x0270 
  BYTE N004163E9; //0x0271 
  BYTE N00416B3C; //0x0272 
  BYTE N004163EA; //0x0273 
  BYTE N001BF11F; //0x0274 
  BYTE N0041C217; //0x0275 
  BYTE N0041C7F3; //0x0276 
  BYTE N0041C218; //0x0277 
  char _0x0278[8];
  BYTE N001BF11C; //0x0280 
  BYTE N0044B621; //0x0281 
  BYTE N0044BBAF; //0x0282 
  BYTE N0044B622; //0x0283 
  BYTE N001BF11B; //0x0284 
  BYTE N00428EB2; //0x0285 
  BYTE N00428924; //0x0286 
  BYTE N00429CC9; //0x0287 
  BYTE N001BF11A; //0x0288 
  BYTE N0042BF59; //0x0289 
  BYTE N0042C536; //0x028A 
  BYTE N0042BF5A; //0x028B 
  BYTE N001BF119; //0x028C 
  BYTE N0042FC21; //0x028D 
  BYTE N0043023C; //0x028E 
  BYTE N0042FC22; //0x028F 
  BYTE N001BF118; //0x0290 
  BYTE water_light_reflection; //0x0291 
  BYTE water_light_reflection_1; //0x0292 
  BYTE N00434BBF; //0x0293 
  BYTE N001BF117; //0x0294 
  BYTE N00441E4F; //0x0295 
  BYTE N004426EA; //0x0296 
  BYTE N00441E50; //0x0297 
  BYTE N001BF116; //0x0298 
  BYTE N004450AC; //0x0299 
  BYTE N0044588B; //0x029A 
  BYTE N004450AD; //0x029B 
  BYTE N001BF115; //0x029C 
  BYTE N0044805A; //0x029D 
  BYTE N00448740; //0x029E 
  BYTE N0044805B; //0x029F 

};//Size=0x02A0

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

class AxisAlignedBox {
public:
  typedef enum {
    FAR_LEFT_BOTTOM = 0,
    FAR_LEFT_TOP = 1,
    FAR_RIGHT_TOP = 2,
    FAR_RIGHT_BOTTOM = 3,
    NEAR_RIGHT_BOTTOM = 7,
    NEAR_LEFT_BOTTOM = 6,
    NEAR_LEFT_TOP = 5,
    NEAR_RIGHT_TOP = 4
  } CornerEnum;
  DirectX::XMFLOAT3 min;
  char __0x000C[0x04];
  DirectX::XMFLOAT3 max;
  char __0x0001C[0x04];

  DirectX::XMFLOAT3 GetCenter() const {
    return DirectX::XMFLOAT3(
      (max.x + min.x) * 0.5f,
      (max.y + min.y) * 0.5f,
      (max.z + min.z) * 0.5f);
  }

  inline const void GetAllCorners(DirectX::XMFLOAT3* corners) const {

    corners[0] = min;
    corners[1].x = min.x; corners[1].y = max.y; corners[1].z = min.z;
    corners[2].x = max.x; corners[2].y = max.y; corners[2].z = min.z;
    corners[3].x = max.x; corners[3].y = min.y; corners[3].z = min.z;

    corners[4] = max;
    corners[5].x = min.x; corners[5].y = max.y; corners[5].z = max.z;
    corners[6].x = min.x; corners[6].y = min.y; corners[6].z = max.z;
    corners[7].x = max.x; corners[7].y = min.y; corners[7].z = max.z;
  }

  DirectX::XMFLOAT3 GetCorner(CornerEnum cornerToGet) const {
    switch (cornerToGet)
    {
    case FAR_LEFT_BOTTOM:
      return min;
    case FAR_LEFT_TOP:
      return DirectX::XMFLOAT3(min.x, max.y, min.z);
    case FAR_RIGHT_TOP:
      return DirectX::XMFLOAT3(max.x, max.y, min.z);
    case FAR_RIGHT_BOTTOM:
      return DirectX::XMFLOAT3(max.x, min.y, min.z);
    case NEAR_RIGHT_BOTTOM:
      return DirectX::XMFLOAT3(max.x, min.y, max.z);
    case NEAR_LEFT_BOTTOM:
      return DirectX::XMFLOAT3(min.x, min.y, max.z);
    case NEAR_LEFT_TOP:
      return DirectX::XMFLOAT3(min.x, max.y, max.z);
    case NEAR_RIGHT_TOP:
      return max;
    default:
      return DirectX::XMFLOAT3();
    }
  }
};//Size=0x0020

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
  virtual void GetTransform(DirectX::XMMATRIX* mTransform); // ClientControllableEntity
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
  char _0x0180[16];
  AxisAlignedBox children_aabb;
  char _0x01B0[208];
  void* chassis; //0x0280 
  char _0x0284[92];

};//Size=0x02E0


enum InputConceptIdentifiers {
  ConceptMoveFB = 0x0,
  ConceptMoveLR = 0x1,
  ConceptMoveForward = 0x2,
  ConceptMoveBackward = 0x3,
  ConceptMoveLeft = 0x4,
  ConceptMoveRight = 0x5,
  ConceptYaw = 0x6,
  ConceptPitch = 0x7,
  ConceptRoll = 0x8,
  ConceptFire = 0xA,
  ConceptCrawl =  0x11,
  ConceptBreathControl = 0x25,
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

class RenderView {
 public:
public:
  DirectX::XMMATRIX transform1; //0x0 
  DirectX::XMMATRIX transform; //0x0040 
  char _0x0080[52];
  float fovY; //0x00B4 
  char _0x00B8[12];
  float aspect; //0x00C4 
  char _0x00C8[24];
  __int32 flags; //0x00E0 
  char _0x00E4[12];
  DirectX::XMMATRIX N01085001; //0x00F0 
  char _0x0130[288];
  float fovX;
  float depthToWidthRatio;
  float fov_scale; //0x0258 
  float N0127B70D; //0x025C 
  DirectX::XMMATRIX view_matrix; //0x0260 
  DirectX::XMFLOAT4X4 N0127B6FC; //0x02A0 
  DirectX::XMMATRIX view_matrix_inverse; //0x02E0 
  DirectX::XMMATRIX projection_matrix; //0x0320 
  DirectX::XMFLOAT4X4 N0127B6CC; //0x0360 
  DirectX::XMFLOAT4X4 N0127B6BC; //0x03A0 
  DirectX::XMFLOAT4X4 N0127B6BD; //0x03E0 
  DirectX::XMFLOAT4X4 view_projection_matrix; //0x0420
  DirectX::XMFLOAT4X4 N0127B69d; //0x0460

};//Size=0x0330

class GameRenderer {
 public:
  char _0x0000[48];
  RenderView* view; //0x0030 
};

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
  ID3D11Device* device; //0x0098 
  ID3D11DeviceContext* device_context; //0x009C 
  char _0x00A0[960];
}; // 0x460 (1120)

class RayCastHit {
public:
  DirectX::XMVECTOR position; //0x0000
  DirectX::XMVECTOR normal;    //0x0010
  char pad_0x0020[80];
};

class IPhysicsRayCaster {
public:

  enum RayCastFlags
  {
    NoCheck = 0,
    CheckDetailMesh = 0x0DB,
    IsAsyncRaycast = 0x2,
    DontCheckWater = 0x0FD,
    DontCheckTerrain = 0x07A,
    DontCheckRagdoll = 0x10,
    DontCheckCharacter = 0x20,
    DontCheckGroup = 0x40,
    DontCheckPhantoms = 0x80,
  };

  virtual bool PhysicsRayQuery(const char* identifier, DirectX::XMVECTOR* from, DirectX::XMVECTOR* to, RayCastHit* hit, int flag, void* PhysicsEntityList);
};

class GameWorld {
 public:
  BYTE pad00[0x20];    // 0x00
  IPhysicsRayCaster ray_caster;  // 0x0020
};

class PhysicsManager {
 public:
  char _0x0000[0x3C];
  IPhysicsRayCaster* ray_caster;
};

class Level {
 public:
  char _0x0000[44];
  fb::String name; //0x002C 
  char _0x0030[80];
  void* N0238D666; //0x0080 
  void* N0238D665; //0x0084 
  void* emitter_manager; //0x0088 
  void* emitter_render_manager; //0x008C 
  char _0x0090[4];
  void* world_render_module; //0x0094 
  PhysicsManager* physics_manager; //0x0098 
  void* N0238D65F; //0x009C 
  GameWorld* game_world; //0x00A0 
};

class ClientGameContext {
 public:
  char _0x0000[12];
  ClientPlayerManager* player_manager; //0x000C 
  void* game_time; //0x0010 
  Level* level; //0x0014 
  void* material_grid_manager; //0x0018 
  void* animation_manager; //0x001C 
  void* model_animation_manager; //0x0020 
  char _0x0024[12];
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
  virtual void GetTransform(DirectX::XMMATRIX* transform, int unknown); //
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

struct MemberInfoData {
  char* name;
};

struct MemberInfo {
  MemberInfoData* data;
};

struct TypeInfo : public MemberInfo{
 TypeInfo *next;
 unsigned __int16 m_runtimeId;
 unsigned __int16 m_flags;
 void* super;
 void* default_instance;
 unsigned __int16 class_id;
 unsigned __int16 last_sub_class_Id;
 void* first_derived_class;
 void* next_silbling_class;
 void* field_infos;
 int total_field_count;
};

class Component {
 public:
  virtual TypeInfo* getType();
};

class GameEntity {
};

class FixAlignmentBase // http://lolengine.net/blog/2012/10/21/the-stolen-bytes
{
protected:
  virtual ~FixAlignmentBase() {}
};

class ClientSoldierEntity : public FixAlignmentBase {
 public:
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
  virtual void GetTransform(DirectX::XMMATRIX* mTransform); // ClientControllableEntity
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
  virtual DirectX::XMFLOAT3* GetVelocity(); //velocity

  char _0x0004[4];
  int flags; //0x0008 
  char _0x000C[16];
  ComponentCollection* components; //0x001C 
  char _0x0020[220];
  CharacterPhysicsEntity* physics_entity;
  char _0x00FC; //0x00FC
  bool has_physiscs_entity; //0x00FD
  char _0x0102[594];
  DirectX::XMVECTOR mesh_forward;
  char _0x0364[120];
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
    uint16_t id;
    uint16_t sub_id;
    int unknown_1;
    int unknown_2;
    Component* component;
  };

  Component* GetFirstComponentOfType(uint16_t class_id, uint16_t last_class_sub_id) {
    ComponentCollectionEntry* entry = (ComponentCollectionEntry*)((DWORD)this + 0x10);

    while (((uint16_t)(last_class_sub_id - class_id) >= (uint16_t)(entry->id - class_id)) == false || entry->component == nullptr) {
      entry++;
      if (entry == (ComponentCollectionEntry*)((DWORD)this + 0x10 + 0x10 * this->playerCount)) return nullptr;  
    }
    return entry->component;
  }
};

class ProjectileEntityData {
public:
  char _0x0000[248];
  float gravity; //0x00F8 
}; //size 0x00C0 (192)

class ShotConfigData {
 public:
  DirectX::XMFLOAT3 m_InitialPosition;//this+0x0000  size 0x0010
  DirectX::XMFLOAT3 m_InitialDirection;//this+0x0010  size 0x0010
  void* m_InitialDirectionScaleByPitch;//this+0x0030  size 0x0004  field 3
  DirectX::XMFLOAT3 m_InitialSpeed;//this+0x0020  size 0x0010
  void* m_InitialSpeedScaleByPitch;//this+0x0034  size 0x0004  field 5
  void* unknown;
  void* unknown1;
  float m_InheritWeaponSpeedAmount;//this+0x0038  size 0x0004
  void *m_MuzzleExplosion;//this+0x003C  size 0x00B0
  ProjectileEntityData *m_ProjectileData;//this+0x0040  size 0x00C0
  ProjectileEntityData *m_SecondaryProjectileData;//this+0x0044  size 0x00C0
  void *m_Projectile;//this+0x0048  size 0x0024
  void *m_SecondaryProjectile;//this+0x004C  size 0x0024
  float m_SpawnDelay;//this+0x0050  size 0x0004
  unsigned __int32 numberOfBulletsPerShell;//this+0x0054  size 0x0004
  unsigned __int32 m_NumberOfBulletsPerShot;//this+0x0058  size 0x0004
  unsigned __int32 m_NumberOfBulletsPerBurst;//this+0x005C  size 0x0004
  byte m_RelativeTargetAiming;//this+0x0060  size 0x0001
  byte m_ForceSpawnToCamera;//this+0x0061  size 0x0001
  byte m_SpawnVisualAtWeaponBone;//this+0x0062  size 0x0001
  byte m_ActiveForceSpawnToCamera;//this+0x0063  size 0x0001
};//size 0x0070 (112)

class FiringFunctionData {
 public:
  char _0x0000[0x54];
  ShotConfigData shot_config_data;
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
  CharacterPoseType current_pose; //0x006C 
  CharacterPoseType next_pose; //0x0070 
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
  virtual void* GetCharacterUserData(); // PlayerCharacterUserData
  virtual fb::EntryComponent* GetEntryComponent();
  virtual bool InVehicle();

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
