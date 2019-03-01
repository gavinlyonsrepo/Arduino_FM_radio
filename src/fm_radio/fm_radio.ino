//******************* HEADER **************
/*
  Name : fm_radio
  Title : Fm-radio and speaker
  Description : Arduino based FM radio using TEA5767 FM module, LM386 module, Audio amplifier
  with KA2284 audio level indicator and 0.96" SSD1306 I2C OLED LCD Display Module.
  The unit can also be used as a speaker(see below). Radio stations are selected via two push buttons
  and Audio Volume via a Potentiometer on the LM386 module. A SPDT controls entry to settings mode.
  Author: Gavin Lyons
  URL: https://github.com/gavinlyonsrepo/Arduino_FM_radio
*/

//*************** Libraries *****************
#include <Wire.h> //I2C comms standard
#include <EEPROM.h> //EEPROM standard
#include <TEA5767.h> //FM module
#include <Button.h> //push buttons
#include <Adafruit_SSD1306.h> //OLED
#include <Adafruit_GFX.h> //OLED

//*************** GLOBALS & DEFINES ********************
//OLED define
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
unsigned long previousMillis = 0;     // will store last time OLED was updated
const long interval = 500;           // interval at which to refresh display (milliseconds)

//Class object  for Fm radio module
TEA5767 Radio;

//Define the push buttons and switch
#define btn_One_pin 12
#define btn_Two_pin 11
#define Switch_pin  10  //vcc is left & main , right is gnd & settings.

//Button objects
Button btn_One(btn_One_pin);
Button btn_Two(btn_Two_pin);
Button Switch(Switch_pin);

//Variables radio
uint8_t  search_mode = 0;
uint8_t  search_direction;
unsigned char buf[5];
double current_freq;
uint8_t  signal_level;

//*************************** SETUP *************
void setup() {
  RadioInit();
  OLEDInit();
  GPIOinit();
  //SerialInit(); // Just needed for debug
}

//******************* MAIN LOOP *****************
void loop() {
  DisplayRadioInfoOLED();
  ScanButtons();
  ScanSetingsSwitch();
}

// ********************* FUNCTIONS ****************

//Init the Serail communications for Debug only.
void SerialInit()
{
  Serial.begin(9600);
  delay(50);
  Serial.println("==== Arduino Radio COMMS UP ====");
  double freq;
  uint8_t num = 0;
  // Print the relevant EEPROM section
  // Get EEPROM data for selected address, 6 stations 6 doubles
  // Each double takes 4 bytes in EEPROM
  // memory address = ((last number in list) * 4) + 1, i = ((i-1)*4)+1
  // so for 5  = ((5-1)*4) + 1 = 17th byte in EEPROM.

  for ( uint8_t i = 1; i <= 6; i++) {
    num = ((i - 1) * 4) + 1;
    Serial.print(num);
    Serial.println(" : ");
    EEPROM.get(num, freq);
    Serial.print("Freq: ");
    Serial.println(freq);
    freq = 0;
  }
}

void GPIOinit()
{
  digitalWrite(btn_One_pin, HIGH);
  digitalWrite(btn_Two_pin, HIGH);
  digitalWrite(Switch_pin, HIGH);
  btn_One.begin();
  btn_Two.begin();
  Switch.begin();
}

void RadioInit()
{
  //init radio module
  Wire.begin();
  delay(500); //I2C init  delay
  Radio.init();
  Radio.set_frequency(96.40); // On power on go to station 96.4
}

void OLEDInit()
{
  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  DrawTitles();
  delay (2000); //Pause to show OLED message to user
  display.clearDisplay();
}

// Function called from main to scan the two push buttons
void ScanButtons()
{
  //When button pressed, search for new station
  if (search_mode == 1)
  {
    if (Radio.process_search (buf, search_direction) == 1)
    {
      search_mode = 0;
    }
  }

  //If forward button is pressed, go up to next station
  if (btn_One.pressed())
  {
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_UP;
    Radio.search_up(buf);
    delay(700); //Pause let TEA5767 tune on Station before next press
  }
  //If backward button is pressed, go down to next station
  if (btn_Two.pressed())
  {
    search_mode = 1;
    search_direction = TEA5767_SEARCH_DIR_DOWN;
    Radio.search_down(buf);
    delay(700); //Pause let TEA5767 tune on Station before next press
  }
}

void  DisplayRadioInfoOLED()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (Radio.read_status(buf) == 1) {
      current_freq =  floor (Radio.frequency_available (buf) / 100000 + .5) / 10;
      signal_level = Radio.signal_level(buf);
      DrawMainScreen();
    }
  }
}

// Draw the initializations screen on start-up on OLED
void DrawTitles() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 1);
  display.println("FM radio");
  display.setCursor(0, 17);
  display.println("G Lyons");
  // draw a white circle, 5 pixel radius
  display.fillCircle(100, 25, 5, WHITE);
  display.display();
}

//Draw the freq number on OLED
// Draw the Signal strength number and graph on OLED
void DrawMainScreen() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(current_freq);
  display.setCursor(80, 1);
  display.print("MHz");
  //print display strength
  display.setCursor(0, 17);
  display.print(signal_level);
  // draw a signal level box (x ,y, w ,h)
  display.drawRect(45, 20, 65, 10, WHITE);
  uint8_t sl = signal_level;
  for ( uint8_t x = 0; x < sl; x++)
  {
    //(x1y1 start x2y2 end of line x1, y1, x2, y2)
    display.drawLine(45 + 4 * x, 20, 45 + 4 * x, 29, WHITE);
  }
  display.display();
  display.clearDisplay();
}

// On Entry to settings mode, Draw the Settings choices on OLED
void DisplaySettings()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(25, 1);
    display.println("Save -> ");
    display.setCursor(25, 17);
    display.println("Load ->");
    display.display();
  }
}

//Monitor SPST settings switch, called from Main,
//If switch is pressed display Settings menu and monitor inputs.
void ScanSetingsSwitch()
{
  uint8_t  ReturnMode;
  //right postion GND
  if (Switch.pressed()) {
    while (1)
    {
      DisplaySettings();

      //check button one. SAVE option
      if (btn_One.pressed()) {
        ReturnMode = SaveEEPROM();
        if (ReturnMode == 1) {
          return;
        }
      }
      //check button two. LOAD option
      if (btn_Two.pressed()) {
        ReturnMode = LoadEEPROM();
        if (ReturnMode == 1) {
          return;
        }
      }
      //Check if switch has gone back to left postion = vcc or Main mode
      if (Switch.released()) {
        display.clearDisplay();
        return;
      }
    }
  }
}

//When User has selected to save or load a station to EEPROM from save or
//load settings screen this function handles it.
//and displays message. Function is passed the Number of memory location to save,
//and mode select between save(2) and load(3) and loaded frequency for display
void DisplaySaveLoadMSG(uint8_t  StationNum, uint8_t mode, double loaded_freq )
{
  uint8_t  MemoryAddress = 1;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (mode == 2) {
    MemoryAddress = ((StationNum - 1) * 4) + 1; // See comment in SerialInit function
    EEPROM.put(MemoryAddress, current_freq);
    display.println("Saved");
    display.setCursor(0, 17);
    display.print(current_freq);

  } else if (mode == 3) {
    display.println("Loaded");
    display.setCursor(0, 17);
    display.print(loaded_freq);
  }
  display.print("->");
  display.println(StationNum);
  display.display();
  delay(1000); //Pause to show OLED message to user
}

// When the user has selected save or load from Settings, this function controls
// the display of the save menu or load menu is passed mode(2 or 3) variable to select which
// and the station number and selected freq if in Load mode.
void DisplaySaveLoadMenu(uint8_t  StationNum, uint8_t mode, double loaded_freq)
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("N: 1-6 ->");
    display.setCursor(0, 17);
    if (mode == 3) {
      display.setTextSize(1);
      display.print(StationNum);
      display.print(" Load -> ");
      display.print(loaded_freq);
    } else if (mode == 2) {
      display.print(StationNum);
      display.println(" Save ->");
    }
    display.display();
  }
}

// Lets User load freq from EEPROM
uint8_t LoadEEPROM()
{
  uint8_t  StationNum = 1;
  uint8_t  memaddress = 1;
  double loaded_freq = 0;

  while (1)
  {
    memaddress = ((StationNum - 1) * 4) + 1; // See comment in SerialInit function
    EEPROM.get(memaddress, loaded_freq);
    DisplaySaveLoadMenu(StationNum, 3, loaded_freq);
    //Top button change the StationNum value 1-6
    if (btn_One.pressed()) {
      StationNum++;
      if (StationNum == 7 ) {
        StationNum = 1;
      }
    }
    //bottom button load the freq and return "one"
    if (btn_Two.pressed()) {
      Radio.set_frequency(loaded_freq);
      DisplaySaveLoadMSG(StationNum, 3, loaded_freq);
      delay(2000); //Pause to show OLED message to user
      return (2);
    }
    //Check if switch has gone back to left postion = vcc or Main mode
    if (Switch.released()) {
      display.clearDisplay();
      return (1);
    }
  }
}

// Lets User Save the current freq to the EEPROM
// Returns a uint8_t value
//2:User has saved a freq
//1:User has returned the SPST to Vcc or Main postion.
uint8_t SaveEEPROM()
{
  uint8_t  StationNum = 1;
  while (1)
  {
    DisplaySaveLoadMenu(StationNum, 2, 0);
    //Top button: change the StationNum value 1-6
    if (btn_One.pressed()) {
      StationNum++;
      if (StationNum == 7 ) {
        StationNum = 1;
      }
    }
    //Bottom button: save the freq and return one
    if (btn_Two.pressed()) {
      DisplaySaveLoadMSG(StationNum, 2, 0);
      delay(2000); //Pause to show OLED message to user
      return (2);
    }
    //Check if switch has gone back to left postion = vcc or Main mode
    if (Switch.released()) {
      display.clearDisplay();
      return (1);
    }
  }
}
//*************************** EOF *****************************
