# Symphony-of-Lights

An Arduino-based music-synchronized LED controller that uses push switches to select different lighting patterns and produces dynamic visual effects through an 8-LED output array.

# About the Project

Symphony of Lights is an interactive embedded systems project that demonstrates how an Arduino can control multiple LEDs through programmed timing, switching logic, and user inputs. The system provides three different LED patterns that can be selected using switches, along with a dedicated stop switch to turn off the lighting sequence.

# Key Features

- Three selectable LED lighting patterns
- 8-channel LED output array for dynamic visual effects
- 3 switches for selecting different lighting patterns
- Dedicated stop switch for immediately turning off the LEDs
- Software debouncing for stable switch inputs
- Randomized LED selections in several lighting sequences
- Timed LED transitions and brightness fading
- Serial Monitor feedback for selected patterns and system status

# Hardware Used

- Arduino microcontroller board
- 8 LEDs
- 4 tactile push switches
- Current-limiting and pull-down resistors
- Breadboard and jumper wires

# Pin Connections

| **Function** | **Arduino Pins** |
| --- | --- |
| LED 1 | Pin 6 |
| LED 2 | Pin 7 |
| LED 3 | Pin 8 |
| LED 4 | Pin 9 |
| LED 5 | Pin 10 |
| LED 6 | Pin 11 |
| LED 7 | Pin 12 |
| LED 8 | Pin 13 |
| Pattern 1 Switch | Pin 5 |
| Pattern 2 Switch | Pin 3 |
| Pattern 3 Switch | Pin 4 |
| Stop Switch | Pin 2 |

# Pattern Controls

- **Switch 1** — Activates Pattern 1
- **Switch 2** — Activates Pattern 2
- **Switch 3** — Activates Pattern 3
- **Stop Switch** — Stops the current pattern and turns all LEDs off

# Video Documentations

https://drive.google.com/drive/folders/1QdBcjabaC0WMGpRr1KzXBAMMZ6dMnCR2?usp=sharing
