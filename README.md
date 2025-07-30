# MGS Remake
## Notes
- Next step is to work on Climb mechanic
    - Single button input to climb shoulder height obstacles and/or leap small distances
    - Refer to following links:
        - https://www.youtube.com/watch?v=THbQaOII5bU
        - https://www.youtube.com/watch?v=6hPArmWkKJQ
        - https://www.youtube.com/watch?v=wKafQYX8fz4
        - https://youtu.be/BJIo5ChGJv4

## July 29, 2025
- Began implementation of Climb mechanic
        - YouTube Link: https://youtu.be/Vxbju_QotS4
    - Created an 'AttachToWall' custom event which draws a line from the center of the capsule 3 radi ahead, checks for collision, and orients the mesh to face the wall if collision is detected
    - Bound this custom event to 'F' key
- Find and import animations for Climb and Crouch Walk
    - Downloaded several animations from Mixamo, created new folder to store assets and animations
    - Retargeted the animations (right click) to 'SKM_Quinn' and saved under 'ThirdPerson\Animations\Climb\...'
        - YouTube Link: https://youtu.be/iE474cUpR-o
- Created a new Blend Space for climbing
    - Set X and Y axis to range from -100 to 100 to match climb speed
    - Added Idle animation to center, ShimmyRight/ShimmyLeft animations to X axis, and ClimbUp/ClimbDown to Y axis
- Also changed the Crouch Walk blend space to use a Mixamo animation instead of previous one

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