#include "Handlers.h"
#include "Utilities.h"
#include "Memory.h"
#include "Profiles.h"

Menu* Handlers::currentMenu = NULL;
Menu* Handlers::mainMenu = NULL;
int Handlers::menuFlag = 0;
bool Handlers::menuChanged = false;
LiquidCrystal* Handlers::lcd = NULL;

void Handlers::setCurrentMenu(Menu* m)
{
  currentMenu = m;
}

Menu* Handlers::getCurrentMenu()
{
  return currentMenu;
}

void Handlers::initMenuThroughHandlers(Menu* m,LiquidCrystal& x)
{
  mainMenu = m;
  
  currentMenu = mainMenu;
  menuFlag = 0;
  
  lcd = &x;
}

void Handlers::backToMainMenu()
{
  Serial.println(F("Back To Main Menu - Handler"));
  
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

//Main Menu - start
void Handlers::currentStatus()
{
  Serial.println(F("Current Status - Handler"));
  
  menuFlag = 1;
  menuChanged = true;
  delay(100);
}

void Handlers::viewProfiles()
{
  Serial.println(F("View Profiles - Handler"));
  
  menuFlag = 2;
  menuChanged = true;
  delay(100);
}

void Handlers::createProfile()
{
  Serial.println(F("Create Profile - Handler"));
  
  menuFlag = 3;
  menuChanged = true;
  delay(100);
}

void Handlers::sound()
{
  Serial.println(F("Sound - Handler"));
  
  menuFlag = 4;
  menuChanged = true;
  delay(100);
}

void Handlers::screenTimeout()
{
  Serial.println(F("Time Settings - Handler"));
  
  menuFlag = 5;
  menuChanged = true;
  delay(100);
}

void Handlers::shutDown()
{
  Serial.println(F("Shut Down - Handler"));
  
  menuFlag = 6;
  menuChanged = true;
  delay(100);
}

//Main Menu - end

//Current Status Menu - start

void Handlers::profileName()
{
  if(Profiles::getCurrentProfile() != NULL)
  {   
    Utilities::stringToCharArray(Profiles::getCurrentProfile()->getName(),Utilities::tempProfileName);
    
    lcd->setCursor(0, 1);
    lcd->write(Utilities::tempProfileName);
  }
}

void Handlers::currentTemperature()
{
  
}

void Handlers::currentHumidity()
{
  
}

void Handlers::runningTime()
{
  
}

void Handlers::stopExecution()
{
  Profiles::setCurrentProfile(NULL);
  currentMenu = mainMenu;
  menuFlag = 0;
}

//Current Status Menu - end

//View Profiles Menu - start

void Handlers::profile1()
{
  Serial.println(F("Profile 1 Handler"));
  
  Profiles* showProfile = Memory::getProfileContainerStart();
  showProfileInfo(showProfile);
}

void Handlers::profile2()
{
  Serial.println(F("Profile 2 Handler"));
  
  Profiles* showProfile = Memory::getProfileContainerStart()->getNextProfile();
  showProfileInfo(showProfile);
}

void Handlers::showProfileInfo(Profiles* p)
{
  lcd->setCursor(0, 1);
  lcd->write("Temp:");
  
  char tempForTemperature[Utilities::getNumberOfDigits(p->getTemperature())+1];
  Utilities::intToCharArray(p->getTemperature(),tempForTemperature);
  
  lcd->write(tempForTemperature);
  lcd->write("C Hum:");
  
  char tempForHumidity[Utilities::getNumberOfDigits(p->getHumidity())+1];
  Utilities::intToCharArray(p->getHumidity(),tempForHumidity);
  
  lcd->write(tempForHumidity);
  lcd->write("%");
}

//View Profiles Menu - end

//Create Profile Menu - start

void Handlers::inputName()
{
  
}

void Handlers::inputTemperature()
{
  
}

void Handlers::inputHumidity()
{
  
}

//Create Profile Menu - end

//Sound Menu - start

void Handlers::soundOn()
{
  Utilities::setBuzzerFlag(true);
  
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

void Handlers::soundOff()
{
  Utilities::setBuzzerFlag(false);
  
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

//Sound Menu - end

//Screen Timeout Menu - start

void Handlers::fiveSeconds()
{
  Memory::changeScreenTimeoutTime(5);
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

void Handlers::thirtySeconds()
{
  Memory::changeScreenTimeoutTime(30);
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

void Handlers::oneMinute()
{
  Memory::changeScreenTimeoutTime(60);
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

void Handlers::twoMinutes()
{
  Memory::changeScreenTimeoutTime(120);
  currentMenu = mainMenu;
  menuFlag = 0;
  delay(100);
}

//Screen Timeout Menu - end
