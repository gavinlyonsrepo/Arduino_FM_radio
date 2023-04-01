[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)


Overview
--------------------
* Name : Arduino_FM_radio
* Title : Fm-radio project for Arduino based eco system.

* Description : Arduino based FM radio using TEA5767 FM module, LM386 Audio amplifier module
with KA2284 audio level indicator and 0.96" SSD1306 I2C OLED LCD Display Module.
The unit can also be used as a speaker(see below). Radio stations are selected via two push buttons
and Audio Volume via a Potentiometer on the LM386 module. A SPDT switch allows the Radio to enter settings mode
where station frequencies can be stored or loaded from the ATmega328's EEPROM.

* Author: Gavin Lyons

Libraries
------------------------

In the "src" folder you will find the  .ino file with C++ source code , it links to a number of 
external libraries.
 
* <TEA5767.h> // FM module https://github.com/andykarpov/TEA5767
* <Button.h> // buttons  1.0.0 https://github.com/madleech/Button 
* <Adafruit_SSD1306.h> // 1.1.2 OLED
* <Adafruit_GFX.h> //v 1.2.2 OLED

Features and Parts List
------------------------------

The Radio outputs selected Frequency and signal strength to the OLED, a graphic is used to display signal level.

In normal mode the two push buttons control freq of radio station. 
One searches up the FM radio band the other down, for a station.

The SPDT switch controls entry to "settings mode" where station frequencies can be stored or loaded from the ATmega328's EEPROM. Six station can be stored. On entry, there are two options LOAD or SAVE. Selected by Push buttons.
If SAVE is selected the user can then select the memory location 1-6 in EEPROM and then press push button 2 to save
current frequency to that location. 
If LOAD is selected user can browse saved stations and select the one they want.

The LM386 module has a potentiometer which controls volume.

The TEA5667 outputs an audio signal which is fed to the LM386 Amplifier module which then sends it to the
speakers. The speakers inputs are monitored by the KA2284 5-Level LED Audio Indicator. Higher the volume voltage
the more LEDs come on.

The unit can be used as a radio or a speaker, by placing a removable audio cable between output
of TEA5767 and input of LM386 Audio amp. This connection is represented by the AUDIO label between
J2 and J3 on schematic.

1. For Radio mode leave cable in.
2. For Headphones Radio mode can  be placed in the socket J2 Audio.
3. For speaker mode remove the cable then connect output of Audio device(PC, phone) to input of LM386 module (J3 Audio)

See eagle diagram and schematic in "doc" subfolder.
See image folder for images of modules used in "doc" subfolder.


Current Consumption:

1. 60mA, low volume.
2. 80-100mA, Medium volume, all audio lights on Level indicator lighting.
3. 120mA to 140mA, Maximum volume.

Parts.

 *    Arduino UNO or NANO
 *    Antenna and Audio cable
 *    2 x Push Button
 *    SPDT switch.
 *    2 x Speakers(~8ohms)
 *    2 x 10Kohms resistors( I2C pull-up)

Modules.

 *    SSD1306 I2C 0.96" 128X64 OLED LCD Display Module. J1
 *    TEA5767 Radio module J2.
 *    ICStation DIY Kit 3V-12V LM386 Super MINI Audio Amplifier module Board. J3 [URL](http://www.icstation.com/icstation-lm386-super-mini-amplifier-board-p-5025.html)
 *    KA2284 5-Level LED Audio Indicator Board Module DIY KIT. J4 [URL]( http://3.bp.blogspot.com/-eO-9YtigXEs/T4lbYAR8BqI/AAAAAAAAAmM/sgNGqV6qTJo/s1600/5-LED-Vu-meter-circuit-using-KA2284.png)


 Schematic
 -----------------------
 ![ScreenShotradio](https://github.com/gavinlyonsrepo/Arduino_FM_radio/blob/master/doc/eagle/fm_radio.png)
