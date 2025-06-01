# DeckBox-CLI

A console based DeckBox interface for debugging and testing only. See the PyQT interface for the production version.

## Overview
The program checks sockets defined by the classes in the connections.h file

## Gamepad Support
On linux gamepads show up under /dev/input/js* and can be accessed via "linux/joystick.h"<br>
deckbox-cli has support for these controllers and can currently read and display raw inputs from them. The end goal is to have a "controller buffer" that contains a stream of controller inputs and have deckbox-cli transmit that buffer over a socket which can be read by the AUV hub, and other programs on the network. 

## multi threading 
Because multiple things must be done at once (read controller/keyboard input, read from/transmit to sockets, display information), multi threading may be implemented, Currently, the code is being optimized so that each of these operations have enough time to occur while running at an acceptable speed.

## TODO
amepad support<br>
controller/command socket

## Compilation

## Usage
