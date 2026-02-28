# MGS Remake
## Notes
- Add multiplayer support for aim offset: https://youtu.be/fAkEbqQH1b8
- Add physics constraint component: https://youtu.be/N5iepSot6XM

## February 27, 2026
- Added BP_Enemy_Ranged and BP_Enemy_Melee
    - A simple enemy which spawns a crossbow or a sword and repeatedly attacks
    - For development purposes, use to test attack animations, hit reactions, damage, etc
- Fixed collision on projectiles
    - Projectiles now have their own object type for the purposes of collision, "Projectile"
    - Character Meshes will generate overlap events, and now when a projectile hits the Actor, it ignores the Capsule and is blocked by the Mesh
- Began implementation of Inventory System
    - Added BPO_ItemMaster
        - An abstract Object Actor meant to store data universal to all inventory objects
        - All future Items which can be put into the inventory system will be made children from this actor
    - Added BP_ItemPickupMaster
        - A blueprint Actor which automatically constructs a static mesh
        - Used to spawn items into the world, allowing the player to find items around the map and add it to their inventory
    - Added BPC_InventorySystem
        - An actor component which uses a Set variable to keep track of items in the inventory
        - Plan to add weight limits, recall an item to hand, remove item from inventory, and interfacing with other components (ie. BPC_StaminaSystem, BPC_CombatSystem)

## February 23, 2026
- Tweak to the melee attack in BPC_CombatSystem
    - Melee attacks will generate three traces, one at 45°, 90°, and 135°, in order to draw the arc of a swing
    - This trace can also generate a single trace directly in front of the character in order to determine a stab
    - These trace results will check if the component hit has a BPC_DamageSystem component, allowing the attack if true or calling to interrupt the attack if false (not yet implemented)
    - System needs tweaking and a lot more research into interrupting animation montages, plan moving forward is the set up points in the animation montage which correlate with this arc of swing and trigger an interrupt with stagger if the character hits a non-damagable surface

## February 22, 2026
- Massive overhaul of various actions, components, and functions
- Added new actor component, BPC_DamageSystem, and interface, BPI_Damagable
    - New actor component can be applied to any actor to add health, limb damage, damage responses, and additional variables
    - Component interacts with other actors via BPI_Damagable interface, which must have functions defined in each actor where needed
    - Interface functions include:
        - GetCurrentHealth function, Input none, Output Health (float)
        - GetMaxHealth function, Input none, Output MaxHealth (float)
        - Heal function, Input Amount (float), Output NewHealth (float)
        - TakeDamage function, Input DamageInfo (structure), Output WasDamaged (boolean)
    - Aforementioned structure variable is defined in S_DamageInfo, which includes:
        - Amount (float)
        - DamageLimb (E_PhysicalSurface)
        - DamageType (E_DamageType)
        - DamageResponse (E_DamageResponse)
        - ShouldDamageInvincible (boolean)
        - CanBeBlocked (boolean)
        - CanBeParried (boolean)
        - ShouldForceInterrupt (boolean)
    - Component will interact with W_HealthBar widget, which pulls Health and MaxHealth from BPI_Damagable to set ProgressBar_Health
    - Actors must create events for Death, LimbCrippled, Blocked, and DamageResponse, and be bound to their respective event dispatchers
- Added new actor component, BPC_StaminaSystem
    - New actor component can be applied to any actor to add stamina, and use event dispatchers to initiate drained stamina events
    - Event ConsumeStamina can reduce stamina by amount input, and can be set to ongoing
        - Call function EndOngoing at end of ongoing action to stop stamina drain
    - Event ReplenishStamina will automatically call 1 second after ConsumeStamina ends, and will wait 2.5 seconds to replenish if stamina is empty
    - Actors must create events for StaminaDrained, and be bound to their respective event dispatcher
- Added new actor component, BPC_CombatSystem
    - New actor component to implement combat functionality dependant on E_WeaponType
    - Event AimBegin and AimEnd controls orientation of the character relative to the camera and calls for crosshair to appear
    - Event DrawBegin and DrawEnd controls the length of an attack's windup, which currently affects Melee damage output and Throwable range output
    - Event Attack picks between three macros; MeleeAttack, RangedAttack, and ThrownAttack
        - MeleeAttack calls OnConsumeStamina event dispatcher, determines the sound to play on attack, and which animation montage to play depending on Draw Time
        - RangedAttack calls for a loaded ranged weapon, LaunchProjectile function, determines the sound to play on fire, and which animation montage to play
        - ThrownAttack calls SpawnProjectile function, LaunchProjectile function, ConsumeStamina event dispatcher, determines the sound to play on throw, and which animation montage to play
    - Reload event, specific to Ranged Weapon Types, it will load a projectile into a ranged weapon and set the weapon to be loaded
    - MeleeTrace function is called on AnimNS_HitDetection, a notify state used in animation montages to trigger something per tick when active
        - Draws a trace sphere around the blade per tick of the attack animation, determines damage based on DrawTime, and calls TakeDamage (Message)
    - Actors must create events for UnEquipWeapon, and be bound to their respective event dispatcher
- Added new actor, BP_NonPlayerCharacter
    - Barebones actor used for testing purposes, and should be used going forward for AI enemies
- Reconfigured numerous files
- Deleted redundant assets
- Added new animations for combat, movement, and a new ABP_MasterCharacter

## January 10, 2026 
- Current AI States
    - Routine, wanders the randomly map and waits at intervals
    - Combat, chases after the player if they are seen and will attack when in range
    - Searching, moves to the last known location of the player if they were seen but then lost sight of them then waits for the max age of its memory to run out then returns to routine unless the player is seen again

- Ai Overview 
  - AiController - AIC_Enemy
    - Contains Perception component, which uses sight sense to detect player pawn based of stimuli placed within the master character
    - Contains State Machine link to manage behavior states

  - Generic_EnemyNPC
    - Based off the same master character as the player, contains variables for health and damage 
    - Linked to the AiController to manage behavior
    
  - Evalulators - uses master base evaluator
    - Current evaluator is a sight based evaluator
        - Handles detecting the player pawn based on line of sight and distance, detecting distance to the precived player, and losing sight of the player then forgetting the player based off max age in the Ai Controller perception component
        
  - Tasks - uses a master base task.
    - Tasks have a start and end event they are for giving a event to the state tree to execute
        - Current tasks include Attack player, Get Random Location, Spawn Weapon. There are included tasks within unreal such as delay and move to location
  
  - State Tree - used to dictate the behavior of the Ai
    - Connects to both the NPC and the AI Controller. Both need to correct context set within them to work
    - Checks all evaluators, tags, booleans, and executes tasks based on the results then transitions based off of the tree and conditions met.

## January 9, 2026
- NOTE: Stamina drain currently only applies to sprinting, need to modify the system from the tutorial to be more modular
    - TBA: Stamina drain when
        - Climbing
        - Jumping
        - Attacking
- Added a Stamina System
    - Tutorial, *How To Set Up A Basic Stamina System*: https://youtu.be/oqqcvd-6aBo
    - Added variables to 'BP_MasterCharacter'
        - 'HasStamina' boolean
        - 'Stamina' float
    - Added custom events to 'BP_MasterCharacter'
        - 'Consume Stamina' custom event, which drains stamina by 0.025, checks locomotion, and either repeats process, replenishes, or stops movement
        - 'Replenish Stamina' custom event, which checks for 0 stamina, and replenishes by 0.01 until full or stamina consuming action begins
    - Integrated stamina system in 'WBP_HUD' by casting BP_MasterCharacter to bindings for progress bar and text box

## January 5, 2026
- Fixed Climb Blendspace in ABP_Manny
- Fixed Sprint mechanic's blending into other locomotion states
- Reconfigured the Climb input to check for other states when attempting to climb

## January 2, 2026
- Imported Combat Mechanics from Tony's Unreal 5.7 'ThirdPersonTemplate' Project
- Updated Project Settings
    - Updated 'Physical Surface' types to include Head, Torso, LeftArm, RightArm, LeftLeg, and RightLeg
    - Updated 'Trace Channels' to include Weapons trace channel
- Features can be found in 'All\Content\_Project\*' and include;
    - 'AimOffsets\AO_Look' aim offset and animations, the default aim offset when unarmed
    - 'AimOffsets\AO_Knife' aim offset and animations, the aim offset to be used when aiming with a knife
    - 'Blueprints\ActorComponents\AC_HealthSystem' actor component, which tracks total health, limb health, and applies health bar overlay via 'WBP_HUD Widget' Widget
        - Tutorial, *How To Create A Basic Health And Limb Damage System*: https://youtu.be/E-OBGsKt63o
    - 'Blueprints\Widgets\WBP_HUD' widget blueprint, a simple overlay with a progress bar and text box for showing the Player Character's health system
    - 'Blueprints\AnimationComponents\AnimNS_HitDetection' blueprint class, used during melee weapon swing animations to determine when 'Weapon Trace' function, and therefore damage, is applied
    - 'Blueprints\FunctionLibrary\BPFL_GameplayTagsFunctions' and '\BPI_GameplayTagFunctions' blueprint functions library and interface, a utility we will use in the future to apply effects for limb damage **(WORK IN PROGRESS)**
    - 'Interfaces\BPI_Interact' blueprint interface, provides framework for Interact action input, allowing Player to pick up weapons off the floor
    - 'Materials\PhysicalMaterials\PM_*' physical materials are mapped to 'PA_Mannequin', the physics asset for 'BP_MasterCharacter' skeletal mesh asset, allowing for designation of limbs for purposes of limb health tracking
        - Updated PA_Mannequin, assigned relevant PM_* to bones
    - 'Props\Pickups\*' contains 'BP_PickupMaster' blueprint class and associated children, allowing for the creation of weapon pickups and their associated properties
    - 'Props\Weapons\*' contains;
        - 'BP_WeaponMaster' blueprint class and associated children, which stores weapon variables, mesh assets, and animations
        - 'Enum_FireMode' enumeration, obsolete but may be used in the future
        - 'Enum_WeaponName' enumeration, which stores the unique name of each weapon child to reference in 'Interact' function
        - 'Enum_WeaponType' enumeration, which stores the general category of each weapon child to reference for purposes of states and animation
    - 'Props\BP_Damager' blueprint class, a simple box which deals damage for the purposes of troubleshooting
- Added 'All\Content\Assets' folder to store imported assets in one simple to find location
- Added Input Actions and configued 'IMC_Default';
    - 'IA_Attack' bound to Left Mouse Button
    - 'IA_Aim' bound to Right Mouse Button
    - 'IA_Interact' bound to E
    - 'IA_Drop' bound to G
- Added Weapon Sockets to 'SK_Mannequin';
    - Tutorial, *How To Create A Weapons System (2.0)*: https://youtu.be/H_Q57Yso9mM
    - Sockets are used to attach the weapon to the Player mesh in the correct location, rotation, and scale
    - Added 'Knife_A_Socket'
    - Added 'Pistols_A_Socket'
- 'BP_MasterCharacter' combat functionality added;
    - Variables added:
        - 'Gameplay Tags Container' references Gameplay Tag Container structure
        - 'CurrentWeaponEnum' references Enum_WeaponName enumerator
        - 'IsAlive' boolean
        - 'IsAttacking' boolean
        - 'IsAiming' boolean
        - 'IsTurning' boolean
        - 'LockedTargetYaw' float 
        - 'Components\Current Weapon' references BP_WeaponMaster object
    - Set 'BP_MasterCharacter' Capsule Component collision to ignore Weapons trace channel
    - Set 'BP_MasterCharacter' Actor Tag to 'Human'
    - 'MeleeWeaponTrace' function, which draws a sphere trace from the base to tip of a melee weapon every frame of an attack animation when notified by 'AnimNS_HitDetection'
    - Changed 'CameraBoom' component Transform Location Z to 45, Camera Target Arm Length to 200, and Camera Socket Offset to 0, 50, 10
    - Pickup Weapon function via 'IA_Interact', which references BPI_Interact to spawn an overlapping weapon in the associated Player socket and deletes the free component
    - Drop Weapon function via 'IA_Drop', which spawns the weapon in front of the Player and deletes from associated socket
    - Attack function via 'IA_Attack', which checks for weapon type and plays associated function
    - Aim function via 'IA_Aim', which lerps CameraBoom > Socket Offset and Character Movement > Max Walk Speed using timeline
    - 'Fire Weapon' Custom Event, playing the fire animation of the associated weapon and drawing a line trace to check for collision, applies point damage if strikes Actor with 'Human' tag
    - 'Swing Weapon' Custom Event, playing the melee swing animation of the associated weapon and draws a sphere trace (refer to MeleeWeaponTrace function and AnimNS_HitDetection)
- 'ABP_Manny' combat animation functionality added;
    - Event Graph tracks current weapon equipped, whether the Player is aiming, and transmits AnimNotify for when attack animation is complete
    - Event Graph tracks the Player's Camera Yaw and Pitch for the purposes of calculating Aim Offset
    - Added Aim Offsets for Unarmed State, 'AO_Look', and Knife State, 'AO_Knife'
- 'ABP_Manny' locomotion has been reconfigured
    - Climb state 'BS_Climb' now works, Idle to Climb (rule) required measuring whether Z velocity is increasing or not
    - Nevermind I lied, it doesn't work
- Added child of 'BP_MasterCharacter', 'BP_Player'
    - Added HUD widget which is overlayed on viewport at start of play
- Improved 'Crouch' and 'Prone' Inputs in 'BP_MasterCharacter'
    - Added transistion animations into custom event for each locomotion state
    - Renamed 'Animation States' to 'Enum_LocomotionStates'
    - 'Locomotion' Macro uses timeline and lerp components to all transistions between locomotion states
    - Removed unnecessary functions and input actions
- Updated 'Sprint' Input in 'BP_MasterCharacter'
    - Only allows sprinting while standing and not aiming

## July 29, 2025
- Began implementation of Climb mechanic
    - YouTube Link: https://youtu.be/Vxbju_QotS4
    - Created an 'AttachToWall' custom event which draws a line from the center of the capsule 3 radi ahead, checks for collision, and orients the mesh to face the wall if collision is detected
    - Bound this custom event to 'F' key
- Find and import animations for Climb and Crouch Walk
    - YouTube Link: https://youtu.be/iE474cUpR-o
    - Downloaded several animations from Mixamo, created new folder to store assets and animations
    - Retargeted the animations (right click) to 'SKM_Quinn' and saved under 'ThirdPerson\Animations\Climb\...'
- Created a new Blend Space for climbing
    - Set X and Y axis to range from -100 to 100 to match climb speed
    - Added Idle animation to center, ShimmyRight/ShimmyLeft animations to X axis, and ClimbUp/ClimbDown to Y axis
- Also changed the Crouch Walk blend space to use a Mixamo animation instead of previous one
- Reintroduced Jump feature
    - Default function of Third Person Template
    - Enable 'Can Jump' in CharacterMovementComponent
    - Set EnhancedActionInput_Jump to 'Jump' and 'Stop Jumping'

## July 28, 2025
- Merged all branches to main and created new 'Experimental' branch
- Fixed bug in 'CheckCollision' function
    - Previously, attempting to leave Prone while character is at any Z-value > 0 would break collision detection
    - Rewrote formula to instead draw a Line Trace from the base of the capsule to the tip of the capsule
- Split 'Prone Hitbox Adjustment' into two event trees
    - When transitioning from Crouch to Prone, it follows the first tree;
        - Capsule Component's Capsule Size from 60 to 35
        - Mesh's Relative Location Z-value from -59 to -34
    - When transitioning from Stand to Prone, it follows the second tree;
        - Capsule Component's Capsule Size from 90 to 35
        - Mesh's Relative Location Z-value from -89 to -34
- Discovered cause of bug: Crouch to Prone Capsule Reset
    - Bug: When the character is Crouched and they attempt to Prone, the capsule will result to Stand dimensions if attempted under an obstacle
    - Cause: When the character attempts to enter Prone while Crouched, the first step is to Un Crouch the player, which resets the Capsule dimensions to Stand.
        - This is why there is a strange visual glitch between the transitions.
        - When under an obstacle, the Un Crouch function resets the Capsule dimensions, causing the mesh to clip into geometry for a split second. The engine resolves this clipping by resetting the Capsule to default (Standing) dimensions as soon as it is able to do so (ie. when leaving the obstacle).
    - Fix: Unsure at this moment, I suspect we'll have to rework the logic somewhere along the Event.

## July 27, 2025
- Added 'Current State' and 'Previous State' enum variables to BP_ThirdPersonCharacter and ABP_Manny
    - Reference enum variables in ABP_Manny\EventGraph
    - Configured Prone transitions to reference Previous State and play correct animation
    - Set is Crouching event now uses enum variable
    - Set is Prone event now uses enum variable
- Reworked Crouch Input and Prone Input
    - Uses enum instead of boolean variables
    - Organized into flow charts to easily follow order of operations
- Reworked Prone Hitbox Adjustment to transition between Stand and Crouch
    - Uses Previous State variable to choose between two float integers
    - **BUG**: When entering Prone from Crouch with object overhead, hitbox resets to Stand, unsure of cause
- Imported CheckCollision function (see below) into Porter's branch
- Prepared to delete Tony branch and merge Porter branch into Main (goodnight sweet prince)

## April 20, 2025
- Condensed CheckOverheadCollision into a Function, allowing to easily add feature into other movement inputs
    - CheckOverheadCollision functions draws a line from the center of mass to Z 180 (standing height of Capsule) and Z 120 (crouching height of Capsule), returning a true/false value for each line to detect collision
    - Two outputs are provided, To Stand and To Crouch, allowing the same function to be used to detect overhead collision from either stance, if it matters
    - Removed line visibility by setting 'Draw Debug Type' to 'None' for both traces
- Added boolean outputs for CheckOverheadCollision Function to determine if the character can stand or crouch from current position
- Reconfigured Crouch Input to check overhead when standing
- Reconfigured Crouch Input to check overhead when crouching from prone, allowing smooth transistion between both states
- Reconfigured Prone Input to check overhead when standing

## April 17, 2025
- Fixed Prone mechanic, now sets speed by adding/subtracting 'CrawlSpeed' to Max Walk Speed
- Added system for Prone Collision by adjusting the Capsule Size and the Mesh's Relative Location
    - YouTube Link: https://youtu.be/cZtltom5Jcw
    - Use Timescale node 'ProneTimescale' so transistion between standing and prone is smooth, transistions from 0 to 1 over 1 second
    - The Prone and Un Prone function are input to Play from Start and Reverse from End respectively
    - Input this 0 to 1 variable into three Lerp nodes, a node which slides between value A and B based upon an Alpha
    - These Lerp values are entered into Set Capsule Size and Set Relative Location
    - EXAMPLE: When character initiates Prone, the timeline scales from 0 (default position) to 1 (proned position)
- Added system to check for objects above head when trying to stand from prone using 'Line Trace by Channel'
    - YouTube Link: https://youtu.be/cZtltom5Jcw
    - Add Line Trace by Channel and Branch nodes before Un Prone function, allowing us to check for an object above the player, and only allow them to stand if False
    - Input Actor's Location into Start vector, this is where the line will trace from
    - Input Actor Rotation, isolate Z-Axis and multiply by 180 units into End vector, this will designate the end of the line to be 180 units above the zero of the Actor's z-axis
    - Enable Persistent in Draw Debug Type, allowing us to see the line above the character when they stand
- Added a box object to the world to test Prone mechanic

## April 15, 2025
- Rebound Crouch to 'C'
- Add new keybind to 'Left Ctrl' called 'IA_SpeedDown'
- Crouch mechanic now checks if character is Prone and vice versa
- Condensed and simplified crouch/prone mechanic
- Moved Prone mechanic into a function, removed delay and separated movement speed into Custom movement mode
- Replaced Sprint input with 'Left Shift' to Run and 'Left Ctrl' to Walk, uses a variable Speed Multiplier to update movement speeds while held for all three movement modes
- Added rudimentary BlendSpace for crawl animations

## April 13, 2025
- Untoggled 'Can Jump' in Nav Movement > Movement Capabilities
- Adjusted 'Max Walk Speed' to 350.0 cm/s
- Adjusted 'Max Walk Speed Crouched' to 250.0 cm/s
- Adjusted 'Crouched Half Height' to 60.0 cm
- Added a 'Sprint' Input
- Set 'Crouch' Input to toggle