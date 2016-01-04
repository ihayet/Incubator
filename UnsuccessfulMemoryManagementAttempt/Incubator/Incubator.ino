/*********UPLOAD************
TX - RX - RESET - GROUND  */

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "Menu.h"
#include "Memory.h"
#include "Utilities.h"

#define BRIGHTNESS 11
LiquidCrystal lcd(9, 10, 12, 13, 8, 7);

#define LEFT 4
#define RIGHT 2
#define SELECT 3

#define FAN1 18
#define FAN2 17
#define LIGHT 19

#define REDLED 6
#define GREENLED 5

#define BUZZER 16

//Menu - properties - start

Menu *mainMenu, *runningMenu;

//Menu - properties - end

Memory* profilesMemory;

String currentStatusMenuItemsString[] = {"Profile Name", "Current Temp", "Current Hum", "Running Time", "Stop", "Back"};
Handlers::handler currentStatusMenuHandler[] = {&Handlers::profileName, &Handlers::currentTemperature, &Handlers::currentHumidity, &Handlers::runningTime, &Handlers::stopExecution, &Handlers::backToMainMenu};

int VIEW_PROFILES_MENU_SIZE;
String viewProfilesMenuItemsString[3];
Handlers::handler viewProfilesMenuHandler[6] = {&Handlers::profile1, &Handlers::profile2, &Handlers::backToMainMenu};

String createProfileMenuItemsString[4] = {"Name: ", "Temp: ", "Hum: ", "Back"};
Handlers::handler createProfileMenuHandler[4] = {&Handlers::inputName, &Handlers::inputTemperature, &Handlers::inputHumidity, &Handlers::backToMainMenu};

String soundMenuItemsString[3] = {"Sound: On", "Sound: Off"};
Handlers::handler soundMenuHandler[3] = {&Handlers::soundOn, &Handlers::soundOff};

String screenTimeoutMenuItemsString[4] = {"Five seconds", "Thirty seconds", "One minute", "Two minutes"};
Handlers::handler screenTimeoutMenuHandler[4] = {&Handlers::fiveSeconds, &Handlers::thirtySeconds, &Handlers::oneMinute, &Handlers::twoMinutes};

String profileMenuItemsString[4] = {"Profile Info", "Select Profile", "Delete Profile", "Back"};
Handlers::handler profileMenuHandler[4] = {&Handlers::profileInfo, &Handlers::selectProfile, &Handlers::deleteProfile, &Handlers::backToMainMenu};

byte *buf = new byte[200];

void setup()
{
  Serial.begin(9600);

  initPeripherals();

  delay(3000);

  profilesMemory = new Memory();

  buildMenu();

  Handlers::initMenuThroughHandlers(mainMenu,lcd);

  welcomeMessage();

  delay(1000);
}

void loop()
{
  Handlers::getCurrentMenu()->detectButtonPress();
  dynamicCheck();
  loadNewMenuIfSelectButtonIsPressed();
  screenTimeoutCheck();
}

void initPeripherals()
{
  lcd.begin(16, 2);
  pinMode(BRIGHTNESS, OUTPUT);

  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(SELECT, INPUT);

  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);
  pinMode(LIGHT, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  digitalWrite(BRIGHTNESS, HIGH);
  digitalWrite(LIGHT, HIGH);
  digitalWrite(BUZZER, LOW);
  
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(FAN1, LOW);
  digitalWrite(FAN2, LOW);
}

void welcomeMessage()
{
  lcd.clear();
  delay(100);
  lcd.setCursor(1, 0);
  delay(100);
  lcd.write("Happy Hatchin'");
  delay(100);
  lcd.setCursor(0, 1);
  delay(100);
  lcd.write("With Love - ratZ");
  delay(100);

  while (true)
  {
    if (digitalRead(LEFT) == HIGH || digitalRead(SELECT) == HIGH || digitalRead(RIGHT) == HIGH)
    {
      delay(100);
      Utilities::startBuzzer();
      Handlers::getCurrentMenu()->displayMenuLCD();
      Memory::setScreenTimeoutStart();
      break;
    }
  }
}

void buildMenu()
{
  String mainMenuItemsString[] = {"Current Status", "View Profiles", "Create Profile", "Sound", "Screen Timeout", "Shut Down"};
  Handlers::handler mainMenuHandler[] = {&Handlers::currentStatus, &Handlers::viewProfiles, &Handlers::createProfile, &Handlers::sound, &Handlers::screenTimeout, &Handlers::shutDown};
  mainMenu = new Menu("Main menu", lcd, 6, mainMenuItemsString, mainMenuHandler);
}

void* operator new(size_t size, void* ptr)
{
  return ptr;
}

void dynamicCheck()
{
  if (Handlers::menuFlag != 0 && Handlers::menuChanged == true)
  {
    if (runningMenu != NULL)
    {
      runningMenu->~Menu();
    }

    switch (Handlers::menuFlag)
    {
      case 1:

        runningMenu = new(buf) Menu("Current Status menu", lcd, 6, currentStatusMenuItemsString, currentStatusMenuHandler);
        break;

      case 2:

        VIEW_PROFILES_MENU_SIZE = Memory::getProfileContainerSize() + 1;
        profilesMemory->profilesToStringArray(viewProfilesMenuItemsString);
        viewProfilesMenuHandler[VIEW_PROFILES_MENU_SIZE - 1] = (Handlers::handler)Handlers::backToMainMenu;

        runningMenu = new(buf) Menu("View Profiles menu", lcd, VIEW_PROFILES_MENU_SIZE, viewProfilesMenuItemsString, viewProfilesMenuHandler);
        break;

      case 3:

        runningMenu = new(buf) Menu("Create Profile menu", lcd, 4, createProfileMenuItemsString, createProfileMenuHandler);
        break;

      case 4:

        runningMenu = new(buf) Menu("Sound menu", lcd, 2, soundMenuItemsString, soundMenuHandler);
        break;
        
      case 5:
        
        runningMenu = new(buf) Menu("Screen Timeout menu", lcd, 4, screenTimeoutMenuItemsString, screenTimeoutMenuHandler);
        break;
        
      case 6:
      
        shutDown();
        break;
        
    }

    Handlers::setCurrentMenu(runningMenu);

    Handlers::menuChanged = false;
  }
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
  unsigned long timeDifference = millis() - Memory::getScreenTimeoutStart();
  
  if (timeDifference > (Memory::getScreenTimeoutTime() * 1000))
  {
    digitalWrite(BRIGHTNESS, LOW);
    
    while(true)
    {      
      if(digitalRead(LEFT) == HIGH || digitalRead(SELECT) == HIGH || digitalRead(RIGHT) == HIGH)
      {
        Utilities::startBuzzer();
        delay(500);
        digitalWrite(BRIGHTNESS, HIGH);
        Memory::setScreenTimeoutStart();
        break;
      }
    }
  }
}

void shutDown()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.write("Shut Down?");
  lcd.setCursor(2, 1);
  lcd.write("Yes");
  lcd.setCursor(12, 1);
  lcd.write("No");
  
  while(true)
  {
    if(digitalRead(LEFT) == HIGH)
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.write("Shutting Down");
      delay(3000);
      
      digitalWrite(BRIGHTNESS, LOW);
      digitalWrite(FAN1, LOW);
      digitalWrite(FAN2, LOW);
      digitalWrite(LIGHT, HIGH);
      digitalWrite(BUZZER, LOW);
      digitalWrite(REDLED, LOW);
      digitalWrite(GREENLED, LOW);
      
      if(runningMenu != mainMenu)
      {
        runningMenu->clearMemoryForThisMenu();
        free(runningMenu);
      }
      mainMenu->clearMemoryForThisMenu();
      free(mainMenu);
    }
    else if(digitalRead(RIGHT) == HIGH)
    {
      delay(100);
      
      break;
    }
  }
}
