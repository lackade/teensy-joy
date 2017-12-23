# teensy-joy

A short program for the Teensy LC to simulate a joystick/keyboard. Ground pins
0 to 3 to generate up/right/down/left respectively; ground pins 4-12 to
generate buttons 1-8.

Grounding Pin 14 for a little less than half a second generates keyboard button
press as follows:

* While button 2 (pin 5) is held down, it generates F2
* While button 3 (pin 6) is held down, it generates F3
* While button 4 (pin 7) is held down, it generates TAB
* Otherwise, it generates ESC
