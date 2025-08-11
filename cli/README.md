# DeckBox-CLI

A console based DeckBox interface for debugging and testing. See the PyQT interface for the production version.<br>
NOTE: For 2025, the cli interface will be the main interface.

## Overview
deckbox-cli provides a unified front end for controlling different aspects of tardigrade. deckbox-cli is not conserned with fancy visual displays and is primaraly used for testing and debugugging.

### Primaray Features
- Gamepad Support
- Mode Switching
- Task Selection
- Display of Telemetry data from sensors
- Manual control of the AUV

## Gamepad Support
On linux gamepads show up under /dev/input/js* and can be accessed via "linux/joystick.h"<br>
deckbox-cli has support for these controllers and can currently read and display raw inputs from them. The end goal is to have a "controller buffer" that contains a stream of controller inputs and have deckbox-cli transmit that buffer over a socket which can be read by the AUV hub, and other programs on the network.<br>
NOTE: controller-backend is intended to replace the controller support section of deckbox-cli, however currently deckbox-cli appears to be the main interface for the AUV so the controller implementation here is more updated than controller-backend.

### Structure
controller.h defines a class implmentation for generic controller support that can get raw controller data. It also defines a generic data structure for storing parsed controller data. You must write a driver in controller backends that converts raw data captured from the generic driver (controller_generic_raw)  and converts it to a controller_generic_profile type which can be used by deckbox-cli.


## Optimization 
Because multiple things must be done at once (read controller/keyboard input, read from/transmit to sockets, display information), the code is being optimized so that each of these operations have enough time to occur while running at an acceptable speed. Addition of any other external device operations needs to be implemented in a way that allows for maximum speed.
## TODO

## Compilation
```
./build.sh
```
## Usage
Use the number keys (1- 6) to change modes<br>
Two control modes are implemented:
### Test mode (1)
```
	all thrusters values are tied to a variable that can be changed with LT1 and RT1, face button 1 turns on thrusters, and face button 2 turns off the thrusters
	power values are only indivated via auv-hub's console output 
```
### Full Manual Control (2)
```
	more refined than mode 1
	each thruster can be set independently
		zero all: face 1
        	zero current: face 2
        	toggle thruster: face 3
        	throttle up: LT2
        	throttle down: LT1
	deckbox-cli will show which thruster is selected and each thruster value

```








For help:
```
./deckbox-cli help
```
For general usage:
```
./deckbox-cli listen
```
