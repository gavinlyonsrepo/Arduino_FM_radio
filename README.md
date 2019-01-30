Overview
--------------------
* Name : fm_radio
* Title : Fm-radio and speaker
* Description : Arduino based FM radio using TEA5767 FM module, LM386 module, Audio amplifier 
with KA2284 audio level indicator and 0.96" SSD1306 I2C OLED LCD Display Module.
The unit can also be used as a speaker(see below). Radio stations are selected via two push buttons
and Audio Volume via a Potentiometer on the LM386 module.

* Author: Gavin Lyons

Libraries
------------------------

In the "src" folder you will find the  .ino file with C++ source code , it links to a number of 
libraries.
 
* <Wire.h> //I2C comms
* <TEA5767.h> //fm module
* <Button.h> // buttons // https://github.com/madleech/Button https://www.arduinolibraries.info/authors/madleech
* <Adafruit_SSD1306.h> //lcd
* <Adafruit_GFX.h> //lcd

All can be found on Arduino website site except the last two , these are on the adafruit site.

Software used
-----------------------------
Eagle 9.1.3

Arduino 1.8.5


Features and Parts List
------------------------------

The two push buttons control freq of radio station. One searches up the FM radio band the other down, for a station.

The LM386 module has a potentiometer which controls volume.

The unit can be used as a radio or a speaker, by placing a removable audio cable between output
of TEA5767 and input of LM386 Audio amp. This connection is represented by the AUDIO label between
J2 and J3 on schematic.

1. For Radio mode leave cable in.
2. Headphones can  be placed in the socket J2 Audio for alternative Radio mode but no volume control is available.
3. For speaker mode remove the cable then connect output of Audio device(PC, phone) to input of LM386 module (J3 Audio)

See eagle diagram and schematic in "doc" subfolder.
See image folder for images of modules used in "doc" subfolder.

Parts.

 *    Arduino UNO or NANO
 *    Antenna
 *    2 x Push Button
 *    2 x Speakers(~8ohms)
 *    2 x 10Kohms resistors( I2C pull-up)

Modules.

 *    SSD1306 I2C 0.96" 128X64 OLED LCD Display Module. J1
 *    TEA5767 Radio module J2.
 *    ICStation DIY Kit 3V-12V LM386 Super MINI Audio Amplifier module Board. J3
 http://www.icstation.com/icstation-lm386-super-mini-amplifier-board-p-5025.html   
 *    KA2284 5-Level LED Audio Indicator Board Module DIY KIT. J4
 http://3.bp.blogspot.com/-eO-9YtigXEs/T4lbYAR8BqI/AAAAAAAAAmM/sgNGqV6qTJo/s1600/5-LED-Vu-meter-circuit-using-KA2284.png

 
 Schematic
 -----------------------
 ![ScreenShotradio](https://github.com/gavinlyonsrepo/Arduino_FM_radio/blob/master/doc/eagle/fm_radio.png)
 
 Copyright
-------------------------------
Copyright (C) 2016 G Lyons This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, see license.md for more details

