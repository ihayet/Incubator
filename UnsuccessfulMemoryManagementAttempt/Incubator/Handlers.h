#pragma once

#include <LiquidCrystal.h>
#include "Profiles.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Menu;   //Forward declaration to avoid recursive inclusion

class Handlers
{
  private:
    static Menu* currentMenu;
    static Menu* mainMenu;
    
    static LiquidCrystal* lcd;
    
    static void showProfileInfo(Profiles* p);
  public:    
    static int menuFlag;
    static bool menuChanged;
    
    typedef void (*handler)();
    
    static void setCurrentMenu(Menu* m);
    static Menu* getCurrentMenu();
    static void initMenuThroughHandlers(Menu* m,LiquidCrystal& x);
    static void backToMainMenu();
  
    //Main Menu
    static void currentStatus();
    static void viewProfiles();
    static void createProfile();
    static void sound();
    static void screenTimeout();
    static void shutDown();
    
    //Current Status Menu
    static void profileName();
    static void currentTemperature();
    static void currentHumidity();
    static void runningTime();
    static void stopExecution();
    
    //View Profiles Menu
    static void profile1();
    static void profile2();
    
    //Create Profile Menu
    static void inputName();
    static void inputTemperature();
    static void inputHumidity();
    
    //Sound Menu
    static void soundOn();
    static void soundOff();
    
    //Screen Timeout Menu
    static void fiveSeconds();
    static void thirtySeconds();
    static void oneMinute();
    static void twoMinutes();
    
    //Profile Menu
    static void profileInfo();
    static void selectProfile();
    static void deleteProfile();
};
