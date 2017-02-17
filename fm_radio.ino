//libaries
#include <Wire.h> //I2C comms
#include <TEA5767.h> //fm module
#include <Button.h> //push buttons
#include <Adafruit_GFX.h> //nokia 5110
#include <Adafruit_PCD8544.h> //nokia 5110


//Class for the LCD display nokia 5110
//Pinout:(SCLK, DIN, DC, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(10, 9, 8, 7, 6 ); 

//Class for Fm radi module
//Pinout SLC and SDA - Arduino pins D5 and D4
TEA5767 Radio; 

//Define the push buttons for serch FM radio forward and back
//Search station up button
Button btn_forward(11, PULLUP); 
//Search station down button
Button btn_backward(12, PULLUP);

//Variables:
double old_frequency;
double frequency;
int search_mode = 0;
int search_direction;
unsigned long last_pressed;
unsigned char buf[5];
int stereo;
int signal_level;
double current_freq;
unsigned long current_millis = millis();

void setup() {
  
  //Internal resistors for buttons
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);

  //debug
  Serial.begin(9600);

    //init LCD 5110
  display.begin();
  //display.setContrast(100);
  display.setContrast(55);
  display.clearDisplay();
    int16_t i=0;
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, BLACK);
   
  
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.setCursor(5,10);
   display.println("FM Radio.");
   display.setCursor(5,30);
   display.println("Gavin Lyons.");  
   display.display();
   delay(1500);
  //I2C
  Wire.begin();
  delay(1000);
  
  //init radio module
  Radio.init();
  Radio.set_frequency(106.106); //On power on go to station 96.4

  display.clearDisplay();
  }

void loop() {

 if (Radio.read_status(buf) == 1) {
    current_freq =  floor (Radio.frequency_available (buf) / 100000 + .5) / 10;
    stereo = Radio.stereo(buf);
    signal_level = Radio.signal_level(buf);
   
   //freq display
   display.setTextSize(2);
   display.setTextColor(BLACK);
   display.setCursor(0,10);
   display.print(display.print(current_freq));
  // display.setCursor(47,15);
  // display.print("MHz");
  // display.setCursor(0,20);
   display.setTextSize(1);
   display.setTextColor(BLACK);
   
   //Strereo or mono ? - display
   //if (stereo) display.print("STEREO"); 
   // else display.print("MONO");
   
   // display level of FM signal..
   display.setCursor(10,35);
   display.setTextSize(1);
   display.setTextColor(BLACK);
   display.print(signal_level);
   display.print("/15 "); 
   

    display.display();
   delay (500);
   display.clearDisplay();

   
   //Draw a signal level triangle...
  //display.drawLine(80, 30, 80, 45, BLACK);
  //display.drawLine(80, 45, 50, 45, BLACK);
 // display.drawLine(50, 45, 80, 30, BLACK);
//   Fill triangle with signal strength
  int sl = signal_level;
  for (int x = 0; x < sl; x++)
   { 
    display.drawLine(50+2*x, 45, 50+2*x, 30, BLACK);
    //display.drawLine(80, 30, 80, 45, BLACK);
 // display.drawLine(80, 45, 30, 0, BLACK);
  }

  
 }
 
     //When button pressed, search for new station
  if (search_mode == 1) {
      if (Radio.process_search (buf, search_direction) == 1) {
          search_mode = 0;
      }
  }
  //If forward button is pressed, go up to next station
  if (btn_forward.isPressed()) {
    Serial.println("button1pressed");
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_UP;
    Radio.search_up(buf);
    delay(1000);
  }
  //If backward button is pressed, go down to next station
  if (btn_backward.isPressed()) {
     Serial.println("button2pressed");
    last_pressed = current_millis;
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_DOWN;
    Radio.search_down(buf);
    delay(1000);
  } 
 
  delay(100);
}

