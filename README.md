# MGS Remake 
## To-Do List
- Enable Custom movement mode so Prone mechanic works
- Tweak movement settings
- Add transitions between Crouch and Prone
- Add BlendSpace for crouch animations
- Add additional animations for crawling

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