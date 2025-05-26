# DeckBox
DeckBox refers to the frontend interface for the AUV

## Overview
The DeckBox program recieves input from the AUV's primary onboard computer (RPI 4) over socket connections while broadcasting overide control data over its own socket. DeckBox's job is to display recived data in a clear and clean format.

## Interfaces
There are two interfaces: a PyQT interface for production use and a CLI interface for testing and debugging. 

## NOTE
The other interfaces (FLTK, XForms, and OPENGL) along with support programs (takeControl, motorControl, and remoteRX) are deprecated.
