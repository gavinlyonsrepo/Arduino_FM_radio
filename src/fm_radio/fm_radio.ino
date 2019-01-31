//******************* HEADER ***********************************
/*
  Name : LED_Display_arduino
  Title : Arduino Based LED Display unit.
  Desc: An Arduino Based LED Display unit with 15 LEDS and 20 lighting modes.
  A Potentiometer controls mode and push button selects it.
  Author: Gavin Lyons
  URL:https://github.com/gavinlyonsrepo/LED_Display_arduino
*/

//*************************** Libraries *****************
#include <Wire.h> //I2C comms
#include <TEA5767.h> //FM module
#include <Button.h> //push buttons
#include <Adafruit_SSD1306.h> //lcd
#include <Adafruit_GFX.h> //lcd

//*************************** GLOBALS ********************
//lcd define
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

//Class for Fm radio module
//Pinout SCK and SDA - Arduino pins D5 and D4
TEA5767 Radio; 

//Define the push buttons for search FM radio forward and back
//create a Button object at pin 12 11
// pin 12 11 and Enables the AVR internal pullup resistor
//Search station up button
Button btn_forward(11); 
//Search station down button
Button btn_backward(12);

//Variables:
int search_mode = 0;
int search_direction;
unsigned long last_pressed;
unsigned char buf[5];
int stereo;
int signal_level;
double current_freq;
unsigned long current_millis = millis();

//*************************** SETUP ************************
void setup() {
  
   //I2C
  Wire.begin();
  delay(1000);
  
   //init radio module
  Radio.init();
  Radio.set_frequency(96.401); //On power on go to station 96.4
  
   //LCD
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.display();
  delay (1000);

  DrawTitles();
  delay (2000);


 //Internal resistors for buttons
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  btn_forward.begin();
  btn_backward.begin();
  
  //debug
  Serial.begin(9600);

  
  display.clearDisplay();
  display.display();
  }

//******************* MAIN LOOP *****************
void loop() {

 if (Radio.read_status(buf) == 1) {
    current_freq =  floor (Radio.frequency_available (buf) / 100000 + .5) / 10;
    stereo = Radio.stereo(buf);
    signal_level = Radio.signal_level(buf);
   
   //The freq  display function
   DrawFreq();
   // The Display level of FM signal function
   DrawSig();
   display.display();
   delay (500);
   display.clearDisplay();
   
 }
 
    //When button pressed, search for new station
  if (search_mode == 1) {
      if (Radio.process_search (buf, search_direction) == 1) {
          search_mode = 0;
      }
  }
  //If forward button is pressed, go up to next station
  if (btn_forward.pressed()) {
    Serial.println("button1pressed");
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_UP;
    Radio.search_up(buf);
    delay(1000);
  }
  //If backward button is pressed, go down to next station
  if (btn_backward.pressed()) {
     Serial.println("button2pressed");
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_DOWN;
    Radio.search_down(buf);
    delay(1000);
  } 
 
  delay(100);
}

// Draw the initializations screen
void DrawTitles(void) {

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 1);
  display.println("FM radio");

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 17);
  display.println("G Lyons");

  // draw a white circle, 5 pixel radius
  display.fillCircle(100, 25, 5, WHITE);

  
  display.display();

}

//Draw the freq number
void DrawFreq(void) {

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(display.print(current_freq));
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(90, 1);
  display.print("MHz");
  
}

// Draw the Signal  strength graph
void DrawSig(void) {
  //print display strength
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 17);
  display.print(display.print(signal_level));

  // draw a signal level box (x ,y, w ,h)
  display.drawRect(45, 20, 65, 10, WHITE);
  Serial.println(signal_level);
  int sl = signal_level;
  Serial.println(sl);
  for (int x = 0; x < sl; x++)
     { 
    //(x1y1 start x2y2 end of line x1, y1, x2, y2) 
    display.drawLine(45+4*x, 20, 45+4*x, 29, WHITE);
    
     }
}
//*************************** EOF *****************************