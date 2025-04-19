# MGS Remake
## Notes
- Currently, the collision capsule cannot be expanded to encompass the full mesh, and the character's movement component is based on the capsule component. If we want to make an accurate mesh for collision purposes, **we need to rebuild our own character**.
- Need to implement collision detect for crouch, crouch to prone, and prone to crouch, likely as a function.

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