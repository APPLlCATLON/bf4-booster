# FairFight

## Client Infos

- FairFightClientUpdate = `E8 ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ? 5F` ->
  - VeniceNetworkSuspiciousKeyMessage
  - VeniceNetworkClientCameraInfoMessageBase

## Method-Events

### AimBotDetect

	/// Adds a frame of data for a given player. 
	/// <p> 
	/// Must be called once per frame, per active player. Do not call for players 
	/// which are not currently spawned or in some other way not part of the  
	/// active game world. Must be called after AimBotDetector_BeginFrame()  
	/// and before AimBotDetector_EndFrame() 
	///   @param playerId Unique player identifier 
	///   @param locX Player center X 
	///   @param locY Player center Y 
	///   @param locZ Player center Z 
	///   @param viewLocX Player camera center X 
	///   @param viewLocY Player camera center Y 
	///   @param viewLocZ Player camera center Z 
	///   @param dirX Player camera direction X 
	///   @param dirY Player camera direction Y 
	///   @param dirZ Player camera direction Z 
	GB_DllExport void AimBotDetector_Add(const GBPublicPlayerId & playerId, float locX, float locY, float locZ, 
	float viewLocX,float viewLocY,float viewLocZ,float dirX, float dirY, float dirZ); 

### WeaponCheatDetect
- `ServerProjectileImpactMessage` ->
  - `WeaponCheatDetector_AddProjImpact`
- `ServerProjectileOnSpawnMessage` ->
 - `WeaponCheatDetector_AddProjectile`

### MatchResults

### PlayerLocation
 - Server
   - `Event_PlayerLocationList_Send`

### ChatMessage
 - Server
   - `ServerPlayerChatMessage` ->
     - `Event_Chat_Send`

### MaxPlayerCount
 - Server
   - `Event_MaxPlayerCount_Send`

### PlayerCount
 - Server
   - `Event_PlayerCount_Send`

### PlayerJoin
 - Server
   - `Event_PlayerJoin_Send`

### PlayerLeave
 - Server
   - `Event_PlayerLeave_Send`

### PlayerList
 - Server
   - `Event_PlayerList_Send`

### Screenshot
 - Client
   - `VeniceNetworkRequestScreenshotMessage`
 - Server
   - `ServerScreenshotReceivedMessage`
   - `Event_PlayerScreenShotJpg_Send`


			/// Sends jpg image data to GameBlocks servers. The image data is limited to slightly less than 1MB.  
			///   @param gbClient The GameBlocks client interface object for your implementation.
                                  Must be valid and should be connected. 
			///   @param sourceId Identifier for game server which this event is for 
			///   @param playerId The game's unique player ID which persists across sessions 
			///   @param imageData Pointer to the jpg image binary data 
			///   @param imageDataNumBytes Byte length of the image binary data 


### SuspiciousKeyPress
 - Client
  - Send if `Insert` or `Delete` was down  (4.12.2013)
  - `VeniceNetworkSuspiciousKeyMessage`
  - E8 ? ? ? ? F3 0F 10 05 ? ? ? ? F3 0F 58 45 08
 - Server
  - `Event_KeyPress_Send`

## Custom Events
Send via `GBClient::SendEvent`

### PlayerSpawn
  - TargetId

### SpottingInfo
  - SpottingType = {0x1, 0x2 ,0x3} // Active, Passive, Radar
  - SpottedId

###  ScorePerMinute
  - TargetId
  - ScorePerMinute
  - TimeInMatch

### CombatScorePerMinute
  - TargetId
  - CombatScorePerMinute
  - TimeInMatch

### WeaponDamage
  - Weapon (Predefined id)
  - Damage

### WeaponRange
  - Weapon (Predefined id)
  - Range

### PlayerKill
  - VictimId
  - KMovTyp
  - KClass
  - VMovTyp
  - VClass
  - BodyPart
  - VictimHealth
  - TeamKill
  - WeaponType
  - Distance
  - Zoomed
  - Spotted