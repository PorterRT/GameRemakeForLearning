# MGS Remake
## Notes
- Add multiplayer support for aim offset: https://youtu.be/fAkEbqQH1b8
- Add physics constraint component: https://youtu.be/N5iepSot6XM
- For future AI controller, a global mediator should be considered to track group movement, detection, and coordination
    - Application of Mediator Pattern: https://youtu.be/y4fE2JdFdvY
- Will make use of object pools instead of constantly deleting and spawning actors, ie. Weapons, Projectiles, Pickups, etc
    - Object Pooling: https://youtu.be/f797l7YTcgc
- Will add a soft move to target function with melee attacks, as well as an Assassinate mechanic
    - Assassinate: https://youtu.be/syd8_y7n-C0

## May 11, 2026
- Added Drag & Drop Operation to Inventory System
- Deleted BI_Inventory
    - Blueprint Interface proved to be redunant, as all communication between Widget and Component is direct
- Added functions 'UseItem' and 'DropItem' to 'AC_InventorySystem'
- Mild tweaks to 'WBP_SideMenu' design and layout
- Add 3D Mesh to Menu?
    - Tutorial: https://youtu.be/XWXXoAgugD8
- Side Note: It may be beneifical in the future to reorganize the Side Menu to be composed of Widget components instead of handling all events in one widget, best to do early

## May 8, 2026
- Created new branch 'InventoryRemake'
- Moved Weapon and Projectile assets to folder '_Project\Assets\'
- Replaced icons with PNG files for transparency
- Added texture 'Icon_InventorySlot'
- Added structure 'F_InventorySlotData'
- Overhauled Inventory System
    - Tutorial: https://youtu.be/E6OSEktabos
    - 'AC_InventorySystem' nows calls functions 'InitializeSlots' on BeginPlay and creates 'WBP_SideMenu'
    - Enhanced Input Action 'IA_SideMenu' now calls for event 'ToggleMenu' in 'WBP_SideMenu'
        - Side Menu no longer sets input to UI Only, now sets between Game Only or Game and UI Only
    - Added InventorySlots 'F_InventorySlotData' array variable, which is used to initialize slots and store F_ItemInfo
    - 'WBP_SideMenu' replaced 'TileView_Inventory' with 'GridPanel_Inventory'
        - New event 'InitializeInventory' creates an 'InventoryRef', calls function 'InitializeInventorySlots', and binds 'UpdateSlot' to 'OnItemAdded' event dispatcher
        - New function 'AddItemNotification' creates widget to show most recent successful item pickup
    - 'WBP_InventorySlot' (previously 'WBP_Item_Tile') nows calls function 'InitUpdateSlot' on Construct

## May 6, 2026
- Edited function 'EquipWeapon' in 'AC_CombatSystem'
- Added 'IA_Number'
    - 'IMC_Default' maps the keyboard numbers 1 to 0
- Added Enhanced Input Action 'IA_Number' to 'AC_InventorySystem'
    - Will integrate a hotkey function to equip weapons assigned to quick access slots

## May 1, 2026
- Moved 'Props' to 'CombatSystem' folder
    - Weapons go in weapon hole, make sense to me
- Modified 'BP_Weapon_Ranged'
    - Finished AttackBegin event
- Modified 'BP_Weapon_Throwable'
    - Added 'Projectile Movement' component
    - For some reason the weapon does not throw? Will resolve
- Added Enumeration 'E_WeaponEffect'
    - Included in 'F_WeaponInfo', allows for weapons to cycle between one damage instance, damage for a duration, or area of effect in 'AttackBegin'

## April 30, 2026
- Modified 'BP_Weapon_Base' and it's children
    - 'BP_Weapon_Base' holds inherited functions and events for all weapons, including;
        - Events 'AttackBegin', 'AttackEnd', and 'SpawnProjectile'
        - Functions 'AttachToOwnerMesh', 'SetWeaponMeshCollision', 'GetDrawValues', 'PlayAttackSound', and 'SpawnImpactEffect'
    - 'BP_Weapon_Melee' in a working state
    - 'BP_Weapon_Ranged' has implemented 'SpawnProjectile' function and 'AttackBegin' event
- Added 'BP_Projectile_Base'
    - A simple Actor, considering whether to handle functions in projectile or weapon blueprint
- Struct 'F_WeaponInfo' updated
    - Now includes 'F_DamageInfo' as variable
- Actor component 'AC_CombatSystem' overhauled
    - Need to update functions 'SpawnNPCWeapon' and 'LaunchProjectile' **NOTE: Will be moved to 'BP_Weapon_Base'
    - Added function 'SpawnWeapon', which is to be used in Inventory to equip a weapon to hand
- Actor component 'AC_InventorySystem' added 'SpawnWeapon' functionality
- Added function 'InteractItem' to 'AC_InventorySystem'
    - Allows items to be used in inventory, each function needs to be set in the function
- BeginPlay event of 'AC_InventorySystem' now spawns Backpack for Owning Actor
    - Will eventually add hot bar function to Inventory

## April 27, 2026
- Deleted numerous redundant item objects
- Added new functions to 'BI_Inventory' and 'BI_ItemObject'
- Added new Enumeration 'E_ItemInteractionType'
- Update to 'WBP_SideMenu' and 'WBP_Item_Tile'
    - 'On Key Down' function now checks for input mapping validity and then executes an interface function via 'BI_Inventory' as determined by macro 'SwitchInputOnKeyDown'
- Updated to 'WBP_ButtonPrompt'
- Started implementation of new weapon items
    - Added 'DT_WeaponTable' and 'F_WeaponInfo' to organize weapon data in one position
    - Added new Actor blueprints 'BP_Weapon_Base' and 'BP_Projectile_Base', which contain inheritable Events that define how each weapon behaves
- Removed extra sockets in 'SK_Mannequin', replaced as Socket 'weapon_r'

## April 23, 2026
- Modified 'AC_InventorySystem'
    - Input Action 'IA_Inventory' now handled in actor component
- Modified 'WBP_SideMenu'
    - Added button prompts to display window, which will dynamically change on item selection
- Modified 'BI_Inventory'
    - Function 'AddItemPickup' now uses 'F_ItemInfo' input instead of row handle
    - Moved 'GetItemObject' to 'BI_ItemObject'
- Modified 'BP_ItemPickup'
    - Construction script now checks for 'ItemInfo', if invalid it sets one based on a handle, and passes 'ItemInfo' directly to spawning Item Object
- Added Blueprint Interface 'BI_ItemObject'
    - Implanted interface on 'BP_ItemObject'

## April 22, 2026
- Deleted contents of Inventory Test
    - Includes 'BI_TileView', 'BP_ObjectEntry', 'WBP_EntryWidget', and 'WBP_Inventory'
- Renamed several files
    - Renamed folder 'Props' to 'Interactables'
    - Renamed 'BP_PickupMaster' to 'BP_ItemPickup'
    - Renamed 'BPO_ItemMaster' to 'BP_ItemObject'
- Added Interact System with interfaces, widgets, etc.
    - Tutorial for Interact System: https://youtu.be/nySnPkzpUn0
    - Added actor component 'AC_InteractSystem'
        - This component handles checking for interactable actors within range, storing them in an array, displaying widgets for interaction, and sending an 'Interact' message ('BI_Interact' interface) to said actors
    - Modified 'BP_ItemPickup'
        - Item mesh will now move to the instigator's location when interacted
    - Modified 'BI_Interact'
        - Added function 'GetInteractionType', which gets the value of an interactable set by 'E_InteractionType'
        - Added function 'GetHoldDuration', which gets the float duration to hold before interacting with an actor
    - Added Actor Blueprint 'BP_Door'
        - A door can be opened and closed via 'Interact' message
    - Added Pawn Blueprint 'BP_NPC'
        - A pawn actor which randomly cycles dialogue and prints to screen via 'Interact' message
    - Added Animation Sequence 'AS_Interact', and Montage 'AM_Interact'
        - Played when AC_InteractSystem calls for 'Interact' message
    - Added User Widget Blueprint 'WBP_Interactable'
        - A HUD component which dynamically displays over objects which can be interacted with
    - Added Enumeration 'E_InteractionType'
        - A simple enumeration to define whether an item is press or hold to interact
    - Modified 'IA_Interact'
        - Changed trigger from 'Hold' to 'Release', allowing dynamic hold times
    - Added Radial Progress Bar
        - Tutorial Link: https://youtu.be/60W4vcnfsg8
        - Added Material 'M_RadialProgressBar'
        - Added Material Instance 'MI_RadialProgressBar'
        - Added User Widget Blueprint 'WBP_RadialProgressBar', which is to be used for radial progress bars

## April 21, 2026
- Modified 'AC_InventorySystem'
    - New function 'SetItemObjectQuantities', which checks all items in inventory to distribute new pickups evenly
    - New function 'AddItemObject', which constructs an 'BPO_ItemMaster', modifies it's quantity, and adds it to the 'Items' set variable
- Modified 'BI_Interact'
    - Function 'GetItemInfo' has new output, 'ItemObject' which is a self reference to instance of 'BPO_ItemMaster'
- Modified 'WBP_SideMenu'
    - When function 'LoadInventory' is called, it adds the set of Items from 'AC_InventorySystem' directly
- Modified 'WBP_Item_Tile'
    - When event 'On List Item Object Set' initializes, it pulls GetItemInfo from BI_Interact, binds an event to 'OnQuantityUpdated', and initializes the item info
    - Now the items update as their quantities change

## April 14, 2026
- Deleted 'WBP_Item_Detail'
- Modified 'WBP_SideMenu'
    - Updated 'TabInventory' to include a 'TileListView' widget and 'TotalWeight' bar
- Added 'BI_Inventory'
    - 'BI_Inventory' is to be applied to actors with an 'AC_InventorySystem' component
    - Handles inventory pull requests, using and equipping items, and dropping items
    - Added functions 'GetInventoryItems', 'EquipItem', 'UseItem', 'DropItemPickup', 'AddItemPickup'
- Modified 'BI_Interact'
    - 'BI_Interact' is now responsible for handling interactions between level objects, Props, and the player
    - It handles passing object information between interacting actors
    - Deleted functions 'UseItem', 'EquipItem', and 'DropItem'

## April 13, 2026
- Update: File structure reformatting, renaming, and cleanup of redundant elements
    - Renaming files in accordance with Recommended Asset Naming Conventions
        - Unreal Documentation: https://dev.epicgames.com/documentation/unreal-engine/recommended-asset-naming-conventions-in-unreal-engine-projects
    - New folder 'StaminaSystem', contains all components relevant to stamina usage
    - New folder 'CombatSystem', contains all components relevant to combat
        - NOTE: Does not contain weapon and projectile assets, see 'Props' for weapon and projectile blueprints
    - New folder 'AdvancedMovementSystem', contains all component relevant to advanced movement
        - WIP: Will include separate component for crouch, prone, climb, vaulting, jumping, sliding, etc.
    - New folder 'StealthSystem', contains all component relevant to stealth and detection
        - WIP: Will include actor component for managing stealth mechanics, will interact with AI Perception
    - Moved 'Actors' folder to '_Project', as 'Blueprints' folder redundant
    - Removed placeholder animations for Crouch (prefix include 'OLD_AnimS_Crouch_*' and 'OLD_BS_Crouch')
    - New folder 'Idle', 'Aim', 'Draw', 'Attack', and 'Interact' in 'Animations\Combat\'
        - 'Idle' folder contains entry poses for each weapon equip
        - 'Aim' folder contains animations when aiming weapons
        - 'Draw' folder contains animations when drawing weapons to attack
        - 'Attack' folder contains animations for attacking with a weapon
        - 'Interact' folders contains miscellanous animations for combat interactions, such as blocking, reloading, drawing/stowing, etc
- Modified 'AC_StaminaSystem'
    - Added blueprint interface 'BI_Stamina', which includes functions for using the stamina system
    - Simplified event 'ConsumeStamina'
    - Added new function 'DrainStamina'
- Modified 'WBP_StaminaBar'
    - Removed redundant casting and cleaned up code
- Added 'DT_ItemTable'
    - Data table with row structs from 'F_ItemInfo'
    - Will serve as primary source for populating instances of item objects with data
- Added 'F_ItemInfo'
    - Structure containing all information pertinent to interactable items
- Modified 'BP_PickupMaster'
    - Construction script now initiates from 'ItemName', a Data Table Row Handle variable meant to pull information from 'DT_ItemTable'
    - 'ItemName' then pulls the 'ItemInfo' struct from the appropriate row, constructs a new 'BPO_ItemMaster' object, passes the Data Table Row Handle and Item Info to the object, sets the quantity, and updates the static mesh
- Modified 'BI_Interact'
    - Added new function 'GetItemInfo', which is to be used instead of casting for specific variables
- Modified 'BPO_ItemMaster'
    - Added new variable 'ItemInfo', a struct variable for 'F_Item_Info' which is set upon spawn
    - Added new variable 'ItemRowHandle', a data table row handle variable which is set upon spawn
    - Kept integer variable 'Quantity' and associated functions, as each object instance stores its own quantity in inventory
    - Added new function 'GetName', which pulls the item name from structure for ease of use
    - Added new function 'GetMaxQuantity', which pulls the maximum stack quantity for an item
    - Removed all prior variables due to redundancy
- Modified 'AC_InventorySystem'
    - Tweaked function 'DropItemPickup' to correctly generate item pickups from inventory
    - Changed function 'AddItemPickup' to be compatible with new data table
- Modified 'WBP_SideMenu'
    - Removed 'TabDisplay' and replaced with a Widget Switcher panel, minimizing bloat and interaction between multiple widget blueprints
    - Deleted 'WBP_Tab_*' widget blueprints, as they are now redundant
    - Added function 'InitializeLimbHealth', which creates limb health bars for each limb and syncs it via event dispatcher with the owner's 'DamageSystem' component
- Modified 'WBP_LimbHealthBar'
    - Renamed primary function to 'InitializeHealthBar'

## April 12, 2026
- Begun rework of Crouch animation
    - Research Mirror: https://dev.epicgames.com/documentation/unreal-engine/mirroring-animation-in-unreal-engine
    - https://youtu.be/crzl7NyqFFk
- Begun rework of Tile View
    - https://youtu.be/NInwimuI7Vg

## April 4, 2026
- Added Crouch animations
    - Imported new animations for idle and walk cycle
    - Created blendspace for Crouch
    - Tweaked Forward and Idle animation to match root
- Tweaks to 'BPC_CombatSystem'
    - Added pure function 'GetPitch', which returns the pitch of the character's body
    - Added variable 'UnderhandThrowMontage', stores animation montage for underhand throw
    - Modified pure function 'GetAttackMontage'
        - Animation montage calculates overhand or underhand throw using GetPitch

## April 3, 2026
- Added structure 'S_HealInfo'
    - Contains variables for determining how a character heals
        - 'Amount', float
        - 'HealLimb', enumeration, specifies which limb to heal
        - 'ShouldForceHeal', boolean, overrides whether character can heal
        - 'ShouldHealAll', boolean, whether healing applies to all limbs equally
        - 'CanHealCripple', boolean, whether healing can repair crippled limbs
- Modified 'BPI_Damagable'
    - Modified function 'Heal'
        - New input 'HealInfo', stucture
        - New output 'WasHealed', boolean
        - Removed input 'Amount' and output 'Health'
    - Added new function 'GetLimbHealth'
- Modified 'BPC_DamageSystem'
    - Added pure function 'GetLimbHealth', which finds the health value (float) and if the limb is crippled (boolean)
    - Added function 'SetLimbHealth', which sets the health value and if the limb is crippled
    - Added new boolean variable 'IsHealable'
    - Modified event dispatcher 'OnLimbUpdate'
        - Now simply calls whenever health of specified limb is updated; characters now handle limb health logic
    - Modified 'Heal' function
        - New input 'HealInfo' and output 'WasHealed'
        - Function now checks if the character can heal, whether to heal all limbs, and returns if the healing was effective
- Modified 'W_DefaultOverlay'
    - Added map variable 'TabClassRef', which stores the User Widget class of each menu tab
    - Added map variable 'TabObjectRef', which stores the User Widget object instance of each menu tab if available
    - Added function 'InitializeTabs', which spawns all tabs from 'TabClassRef', collapses their visibility and adds them to 'TabObjectRef'
    - Modified function 'SetTabDisplay', which sets visibility for already existing tabs to visible if available
    - Modified function 'ClearTabDisplay', which sets visibility for all tabs to collapsed
    - Upon widget construct, function 'InitializeTabs' spawns all the widgets needed for the menu
- Modified 'W_Tab_Status' and 'W_Item_LimbHealthDisplay'
    - Tab now handles all spawning and organizing of limb health bars
    - Limb health bars update on changes to limb health, values are passed from tab
- Updated 'BPO_ItemMaster_Consumable'
    - Consumables now use 'HealInfo' structure variable
- Updated event 'LimbUpdate' in 'BP_MasterCharacter' and 'BP_Enemy_Melee'
- Deleted 'BP_Enemy_Ranged'

## March 30, 2026
- Tweaked 'BPC_DamageSystem'
    - Corrected the handling of limb damage, calling for cripple limb, and tracking the condition of limbs
- Renamed 'W_Item_BoxDisplay' to 'W_Item_Tile'
- Renamed 'W_Item_ContextWindow' to 'W_Item_Detail'
- Tweaked 'W_Item_Tile'
    - Added a border to the item which changes colour upon selection

## March 28, 2026
- Reconfigured 'W_DefaultOverlay'
    - Added function 'OpenMenu', which brings up the inventory overlay
    - Added function 'CloseMenu', which closes the inventory overlay and returns input to game
    - Added function 'InitializeQuickAccess', *WORK IN PROGRESS*
    - Added function 'SetTabDisplay', sets the current tab when a Selection button is released
    - Added function 'ClearTabDisplay', clears the tab display window, effectively resetting the overlay
    - Will remove function 'OpenInventory' once all features fully integrated
- Reconfigured 'W_Tab_Status'
    - Autopopulates the display tab with six limbs via 'W_Item_LimbHealthDisplay' widget
    - 'W_Item_LimbHealthDisplay' widget pulls information about it's specified limb from owning character's 'BPC_DamageSystem' component, if present
- Added 'W_Item_BoxDisplay' and 'W_Item_ContextWindow'
    - Box display is used to show items at a glance, with the icon, item name and quantity of items in inventory
    - Context window is used to display further information about an item when hovered over, including description, category, value, and weight
- Added 'W_Tab_Crafting'
- Added 'W_Tab_Equipment'
- Added 'W_Tab_Inventory'
- Added enumeration 'E_MenuTab'

## March 27, 2026
- Added new input to 'Heal' function in 'BPI_Damagable'
- Modified 'BPC_DamageSystem'
    - Tweaked 'Heal' function to check for limb to heal if specified, otherwise it heals all by an equal amount
    - Added new function 'DamageLimb', receiving taken damage and multiplying it based on the limb injured to reflect vulnerability of different limbs
    - Added new function 'HealLimb', which either heals all limbs by equal amount or a specified limb by amount
    - Event dispatcher 'OnLimbCrippled' now called in 'DamageLimb' function
- Modified 'Heal' interface function in 'BP_MasterCharacter'
    - Requests limb to be healed
- Reconfiguring inventory overlay *WORK IN PROGRESS*
    - Added several buttons to cycle between tabs
    - Added 'W_Tab_Status' and 'W_Item_Limb', which shows each individual limb, health bar, and prompt to heal

## March 23, 2026
- Added event 'Delay Recovery' to 'BPC_StaminaSystem'
    - Input an amount of time in seconds to delay the recovery of stamina
- Changed function 'ConsumeStamina' in 'BPC_CombatSystem'
    - Function checks if character has a stamina system component, then compares the weapon stamina drain to current stamina
    - After attacking, stamina recovery is delayed by 2 seconds
- Removed event dispatcher 'OnConsumeStamina' in 'BPC_CombatSystem'

## March 21, 2026
- Fixed weapon collision detection
    - Weapons with hit detection now draw a box trace matching the collision box
- Added default weapon to spawn in BPC_CombatSystem
    - Only to be used for NPCs that do not use an inventory

## March 16, 2026
- Modifications to 'BPC_CombatSystem'
    - Attack animation montages are now set in the combat system component instead of per item
    - Added Function 'MakeAttack', which conducts all calculations and functions for dealing damage depending on the weapon type
    - Added Function 'GetAttackMontage', which selects the animation to be played based on draw length and weapon type
    - Event 'Reload' checks if the character has an inventory, gets the ammo, decrements it if available, plays the reload montage, and spawns a projectile
- Modifiations to 'BPC_InventorySystem'
    - Added Event 'EquipWeapon' to spawn a weapon in character hand
    - Added Function 'GetAmmo' to check if a weapon's ammo class is available for use, and is referenced elsewhere such as in 'BPC_CombatSystem'
    - Weapons can be equipped from the inventory by pressing E after selecting the item
- Addition of 'BP_WeaponMaster' (+children)
    - An Actor with a Skeletal Mesh and a Collision Box, with included functionality for dealing damage via collision and spawning projectiles
    - BPO_Weapon in the Inventory make reference to the BP_Weapon class
    - Attempting to tweak hit detection, ensuring that the intended limb is hit when attacking
- Removal of previous skeletal mesh component 'BP_WeaponMaster,' and 'BP_WeaponPickup'
    - Previous weapon system is now redundant, was based on adding a skeletal mesh to the actor with a component, disallowing further implemention of collision boxes, trails, mesh modifications, etc.
    - Weapon pickup now replaced by BPC_InventorySystem
    - Weapons now replaced by BP_WeaponMaster (_Project > Props > Weapons)
- Tutorial Links & Resources
    - Inventory System: https://youtu.be/egDxfhr4kzM (Part 1 to 6)
    - Melee Combat System: https://youtu.be/DC7XkWXAKoE
    - Projectile Launch System: https://youtu.be/hkQ9bEwpfV8

## March 7, 2026
- Added BPO_ItemMaster_Weapon
    - Will eventually replace current weapon system, including variable values and damage detection
- Added focus path to W_ItemDisplay
    - Clicking on or pressing tab with items in inventory will show which items are being selected

## February 28, 2026
- Modified actor BP_Damager
    - Damager now has an updated mesh and collision box which only interacts with actor meshes
    - HitActors set variable will store what actor enters the collision box, deal damage to it once, and will not deal damage again until the actor leaves the box, removing it from the set
    - Damager can be disabled with one click in the World Editor via instance 'EnableDamager'
- Modified Object Channels
    - Found in Edit > Project Settings > Engine - Collision > Object Channels
    - Objects can have their collision object type be set as 'Damager', meaning an Actor's Capsule Component will ignore the object while the Mesh will overlap it, allowing more accurate hit results
- Added new widget blueprints; W_ItemDisplay and W_ItemContainer
    - W_ItemDisplay is for an individual item within the BPC_InventorySystem
    - W_ItemContainer is the inventory screen that is overlayed by BPC_InventorySystem, which auto-populates with the items from the component when brought on screen
    - UI Inputs disable all other inputs, inputs must be added into W_ItemContainer in order to respond
        - Currently, 'Escape' and 'I' keys are bound to exit the inventory
- Added temporary 'I' input to BP_MasterCharacter
    - Calls a function in BPC_InventorySystem to display inventory widget, set input to UI, and initalize the inventory
- Added enable Widget input to BPC_InventorySystem
    - A simple boolean which signals whether to add a widget to the character
- Added BPO_Valuable_Gold and BPO_Valuable_Silver
    - Simple static meshes with values, names, and category set, made for development purposes

## February 27, 2026
- Added BP_Enemy_Ranged and BP_Enemy_Melee
    - A simple enemy which spawns a crossbow or a sword and repeatedly attacks
    - For development purposes, use to test attack animations, hit reactions, damage, etc
- Fixed collision on projectiles
    - Projectiles now have their own object type for the purposes of collision, "Projectile"
    - Character Meshes will generate overlap events, and now when a projectile hits the Actor, it ignores the Capsule and is blocked by the Mesh
- Recast ABP_MasterCharacter to Character ref
    - Done to allow BP_Enemy_* to successfully use animation blueprint now that they are no longer children of BP_MasterCharacter
    - With how many functions are now based on components, there were almost no conflicts
    - Locomotion states did require casting to BP_MasterCharacter, should transfer locomotion options to component in the future
- Began implementation of Inventory System
    - Repurposed BPI_Interact
        - Created function to Interact (Message) with an Instigator input
    - Added BPO_ItemMaster
        - An abstract Object Actor meant to store data universal to all inventory objects
        - All future Items which can be put into the inventory system will be made children from this actor
    - Added BP_ItemPickupMaster
        - A blueprint Actor which automatically constructs a static mesh
        - Used to spawn items into the world, allowing the player to find items around the map and add it to their inventory
    - Added BPC_InventorySystem
        - An actor component which uses a Set variable to keep track of items in the inventory
        - Current implementation includes add item to inventory and drop item pickup from inventory
        - Plan to add weight limits, inventory UI, equip item, and interfacing with other components (ie. BPC_StaminaSystem, BPC_CombatSystem)

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