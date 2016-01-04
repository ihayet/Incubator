#pragma once                    //ensures that this file is defined only once - alternate way of writing the following:
                                //#ifndef Handlers_H
                                //#define Handlers_H
                                //#endif

#include <LiquidCrystal.h>

#define REDLED 5
#define GREENLED 6

#define LEFT 4
#define RIGHT 2
#define SELECT 3

#define FAN 18
#define BOX 17
#define LIGHT 19

#define DHTPIN A0                                                      //analog pin that is connected to the Digital Humidity and Temperature Sensor
#define DHTTYPE DHT11                                                  //type of the Digital Humidity and Temperature Sensor

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Menu;   //Forward declaration to avoid recursive inclusion

class Handlers
{
  private:
    static Menu* currentMenu;                                                       //currentMenu is used to call the detectButtonPress in loop
    static Menu** menuContainer;                                                    //Array of Menu objects
    
    static LiquidCrystal* lcd;
  public:       
    typedef void (*handler)();                                                      //Pointer to a specific type of function that returns void and has nothing as parameter - 
                                                                                    //Menu objects are constructed using arrays of handler function pointers that are associated 
                                                                                    //with the menu items - When an item is selected the respective handler function is called
                                                                                    //using the value from the handler function pointer associated with the selected item
                                                                                    //See detectButtonPress functino in Menu.cpp
    
    static void setCurrentMenu(Menu* m);
    static Menu* getCurrentMenu();
    static void initMenuThroughHandlers(Menu** m,LiquidCrystal& x);
    static void backToMainMenu();
  
    //Main Menu - handler functions
    static void currentStatus();
    static void newSettings();
    static void sound();
    static void rotation();
    
    //Current Status Menu - handler functions
    static void target();
    static void currentTemperature();
    static void currentHumidity();
    static void stopExecution();
    
    //New Settings Menu - handler functions
    static void temp();
    static void hum();
    static void start();
    
    //Sound Menu - handler functions
    static void soundOn();
    static void soundOff();
};
