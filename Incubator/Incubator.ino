/**********************************
Author: Ishrak Hayet
Platform: Arduino UNO - Atmega328P
Date: 28-DEC-2015

Purpose:
This is a simple incubator control
system with an OOP based menu.
The system has been built on
the Atmega328p microcontroller,
bootloaded with Arduino
bootloader.
Please check this out:
https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard

It was intended to have profile
controls i.e. preset templates of
egg types that could be started
by selecting the profile. But, due
to the SRAM constraints of Atmega
328p, the profile controls have
been omitted to ensure memory
optimization.

The intended egg hatching
requirements will have to be set
every time when starting a new
setting.

Non-volatile memory storage/
retrieval has been ensured to
safeguard against power failure.
When the system resumes from a
power failure it will pick up from
the previous settings and start
running without any intervention.

The heat source 60W light bulb is
controlled with a 5V-220V relay.
So, it is not possible to dim the
light as it would have been if a
TRIAC was used instead. Therefore,
the temperature control involves
a simple if/else conditioning
instead of a PID control.
**********************************/

/*********UPLOAD************
TX - RX - RESET - GROUND  */

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <DHT.h>
#include "Menu.h"
#include "Memory.h"
#include "Utilities.h"

#define BRIGHTNESS 11                                    //pin that triggers the LCD backlight
LiquidCrystal lcd(9, 10, 12, 13, 8, 7);                  //LiquidCrystal object

#define LEFT 4                                           //left navigation button
#define RIGHT 2                                          //right navigation button
#define SELECT 3                                         //select navigation button

#define FAN 18                                           //pin that controls the fan - (12V Brushless DC motors)
#define BOX 17                                           //pin that controls the rotation of the egg platform
#define LIGHT 19                                         //pin that controls the relay and the 60W light bulb (The relay is normally closed with the 5V line being low - the light bulb is on)

#define REDLED 5                                         //red colored led that is lit up when the incubator is not running
#define GREENLED 6                                       //green colored led that is lit up when the incubator is running

#define BUZZER 16                                        //pin that controls the buzzer - buzzer functionalities are defined in Utilities - buzzer is turned on or off from the sound option

//Menu - properties - start

Menu *mainMenu, *currentStatusMenu, *newSettingsMenu, *soundMenu, *screenTimeoutMenu;
Menu* menuContainer[4];

//Menu - properties - end

#define SCREEN_TIMEOUT_TIME 10                           //time in seconds after which the lcd backlight automatically goes off - reduces power consumption

unsigned long screenTimeoutStart;                        //the start time to keep track of the screen timeout using millis

Memory* profilesMemory;

void setup()
{
  Serial.begin(9600);

  initPeripherals();

  delay(3000);

  profilesMemory = new Memory();

  buildMenu();
  
  menuContainer[0] = mainMenu;
  menuContainer[1] = currentStatusMenu;
  menuContainer[2] = newSettingsMenu;
  menuContainer[3] = soundMenu;
  menuContainer[4] = screenTimeoutMenu;

  Handlers::initMenuThroughHandlers(menuContainer,lcd);

  welcomeMessage();

  delay(1000);
}

void loop()
{
  if(Handlers::getCurrentMenu()->detectButtonPress() < 4)
  {
    screenTimeoutStart = millis();
  }
  loadNewMenuIfSelectButtonIsPressed();
  screenTimeoutCheck();
  Utilities::controlSystem();
}

void initPeripherals()
{
  lcd.begin(16, 2);
  pinMode(BRIGHTNESS, OUTPUT);

  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(SELECT, INPUT);

  pinMode(FAN, OUTPUT);
  pinMode(BOX, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  digitalWrite(BRIGHTNESS, HIGH);
  digitalWrite(LIGHT, HIGH);
  digitalWrite(BUZZER, LOW);
  
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(FAN, LOW);
  digitalWrite(BOX, LOW);
  digitalWrite(LIGHT, HIGH);
}

void welcomeMessage()
{
  screenTimeoutStart = millis();
  
  lcd.clear();
  delay(100);
  lcd.setCursor(1, 0);
  delay(100);
  lcd.write("Happy Hatchin'");
  delay(100);
  lcd.setCursor(0, 1);
  delay(100);
  lcd.write("With Love - ratZ");
  
  if(Memory::getResumeByte() == 2)
  {
    delay(5000);
    Utilities::startBuzzer();
  }
  else
  {
    delay(3000);
  }

  Handlers::getCurrentMenu()->displayMenuLCD();
}

void buildMenu()
{
  String mainMenuItemsString[] = {"Current Status", "New Settings", "Sound", "Rotation"};
  Handlers::handler mainMenuHandler[] = {&Handlers::currentStatus, &Handlers::newSettings, &Handlers::sound, &Handlers::rotation};
  mainMenu = new Menu("Main menu", lcd, 4, mainMenuItemsString, mainMenuHandler);
  
  String currentStatusMenuItemsString[] = {"Target:", "Current Temp:", "Current Hum:", "Stop", "Back"};
  Handlers::handler currentStatusMenuHandler[] = {&Handlers::target, &Handlers::currentTemperature, &Handlers::currentHumidity, &Handlers::stopExecution, &Handlers::backToMainMenu};
  currentStatusMenu = new Menu("Current Status menu", lcd, 5, currentStatusMenuItemsString, currentStatusMenuHandler);
  
  String newSettingsMenuItemsString[] = {"Temp: ", "Hum: ", "Start", "Back"};
  Handlers::handler newSettingsMenuHandler[] = {&Handlers::temp, &Handlers::hum, &Handlers::start, &Handlers::backToMainMenu};
  newSettingsMenu = new Menu("New Settings menu", lcd, 4, newSettingsMenuItemsString, newSettingsMenuHandler);
  
  String soundMenuItemsString[3] = {"Sound: On", "Sound: Off"};
  Handlers::handler soundMenuHandler[3] = {&Handlers::soundOn, &Handlers::soundOff};
  soundMenu = new Menu("Sound menu", lcd, 2, soundMenuItemsString, soundMenuHandler);
}


void loadNewMenuIfSelectButtonIsPressed()
{
  if (Menu::selectButtonPressed == true)
  {
    Handlers::getCurrentMenu()->displayMenuLCD();
    Menu::selectButtonPressed = false;
  }
}

void screenTimeoutCheck()
{
  unsigned long timeDifference = millis() - screenTimeoutStart;
  
  if(timeDifference < 0)
  {
    screenTimeoutStart = millis();  //rollover
  }
  
  if (timeDifference > (SCREEN_TIMEOUT_TIME * 1000))
  {
    digitalWrite(BRIGHTNESS, LOW);
    
    /*
    while(Utilities::runningFlag != true)
    {      
      if(digitalRead(LEFT) == HIGH || digitalRead(SELECT) == HIGH || digitalRead(RIGHT) == HIGH)
      {
        Utilities::startBuzzer();
        delay(500);
        digitalWrite(BRIGHTNESS, HIGH);
        screenTimeoutStart = millis();
        break;
      }
    }
    */
  }
}
