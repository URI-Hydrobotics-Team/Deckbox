# DeckBox-CLI

A console based DeckBox interface for debugging and testing only. See the PyQT interface for the production version.

## Overview
The program checks sockets defined by the classes in the connections.h file

## Gamepad Support
On linux gamepads show up under /dev/input/js* and can be accessed via "linux/joystick.h"<br>
deckbox-cli has support for these controllers and can currently read and display raw inputs from them. The end goal is to have a "controller buffer" that contains a stream of controller inputs and have deckbox-cli transmit that buffer over a socket which can be read by the AUV hub, and other programs on the network.<br>
NOTE: controller-backend is intended to replace the controller support section of deckbox-cli, however currently deckbox-cli appears to be the main interface for the AUV so the controller implementation here is more updated than controller-backend.



###Structure
controller.h defines a class implmentation for generic controller support that can get raw controller data. It also defines a generic data structure for storing parsed controller data. You must write a driver in controller backends that converts raw data captured from the generic driver (controller_generic_raw)  and converts it to a controller_generic_profile type which can be used by deckbox-cli.



## Optimization 
Because multiple things must be done at once (read controller/keyboard input, read from/transmit to sockets, display information), multi threading may be implemented, Currently, the code is being optimized so that each of these operations have enough time to occur while running at an acceptable speed. Polling sockets before reading from them to check rediness has been implemented.

## TODO
amepad support<br>
controller/command socket

## Compilation

## Usage
