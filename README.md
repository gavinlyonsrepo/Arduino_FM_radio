Overview
--------------------
* Name : Arduino Fm-radio
* Title : Fm-radio and speaker
* Description : Arduino Fm radio module using TEA5767 fm module, LM386 module Audio AMP 
with KA2284 audio level indicator and 0.96" SSD1306 I2C OLED LCD Display Module.
The unit can be used as a radio or a speaker, by placing a removeable audio cable between output
of TEA5767 and input of LM386 Audio AMP. For Radio mode leave cable in, for speaker mode remove the cable 
 from TEA5767 socket and connect to Output of Audio device: PC, phone etc.
* Author: Gavin Lyons

Libraries
------------------------

In the src folder you will find the arduino .ino file with C++ source code , it includes a number of 
libraries.
 
* <Wire.h> //I2C comms
* <TEA5767.h> //fm module
* <Button.h> //push buttons
* <SPI.h>
* <Adafruit_SSD1306.h> //lcd
* <Adafruit_GFX.h> //lcd

All can be found on Arduino website site except the last two , these are on the adafruit github.

Parts List
------------------------------

See fritzing diagram in "doc" for assembly instruction and schematic. 
You will need [fritzing](https://en.wikipedia.org/wiki/Fritzing) software to open this.


 *    PSU or battery 7-12V
 *    Case
 *    Arduino uno  or NANO
 *    TEA5767 Radio module
 *    Antenna
 *    SSD1306 I2C 0.96" 128X64 OLED LCD Display Module for Arduino 
 *    2x Push Button
 *    ICStation DIY Kit 3V-12V LM386 Super MINI Amplifier Board
 *    http://www.icstation.com/icstation-lm386-super-mini-amplifier-board-p-5025.html   
 *    KA2284 Audio Level indicator DIY KIT   *  http://3.bp.blogspot.com/-eO-9YtigXEs/T4lbYAR8BqI/AAAAAAAAAmM/sgNGqV6qTJo/s1600/5-LED-Vu-meter-circuit-using-KA2284.png
 *   2x Speakers
 
 
 Copyright
-------------------------------
Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details

