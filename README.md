# Digitized Die

#### Digitized version of "rollable" dice via ESP32 microcontroller.
Options for following "dice" options:
- d2 (coin flip)
- d4 (pyramid dice)
- d6 (standard dice)
- d8 (8 sided dice)
- d10 (10 sided dice)
- d12 (12 sided dice)
- d20 (20 sided dice)
- d100 (percentage value) [IN PROGRESS]

***

## SETUP

1. Connect via usb & use flash software (such as Arduino IDE) to upload "digitized_die.ino"
2. Once uploaded, will automatically function once connected to 3.3v/5v power source (3.3v recommended)
3. Button 1 (D19) "Select" & Button 2 (D21) is "Option"

***

## REQUIREMENTS
## For use with ESP32 microcontroller:
Pin Setup:
| Pin | Function       | Description                |
|-----|----------------|----------------------------|
| GPIO7 | 3V3          | Power supply               |
| GPIO6 | GND          | Ground                     |
| D15   | GPIO         | Data input/output          |
| D2    | GPIO         | Data input/output          |
| D4    | GPIO         | Data input/output          |
| RX2   | GPIO         | Data input/output          |
| TX2   | GPIO         | Data input/output          |
| D5    | GPIO         | Data input/output          |
| D19   | GPIO         | Data input/output          |
| D21   | GPIO         | Data input/output          |
|-------|--------------|----------------------------|

***

**Link to project:** https://github.com/JeshuaLinderJ/digitized_die

***

## Future development

Planned features and implementations:
Code:
- Multicore threading for faster processing
- Improved menu UI
- More UX feedback
- Multiple dice thrown at once
- Improved sprites
- Refactored drawing logic for more efficient display
- More sprite frames for animated roll
- Perhaps another button for improved navigation
- Audio capability

Implementation:
- 3d printed casing mimicking real dice
- Portable setup with battery
- Future implementation with GUI linked DnD module project

***

## References:

https://imgur.com/a/SSS1urt

