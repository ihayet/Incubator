#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LiquidCrystal.h"
#include "Item.h"

#define BRIGHTNESS 11

#define LEFT 4
#define RIGHT 2
#define SELECT 3

#define FAN1 18
#define FAN2 17
#define LIGHT 19

class Menu
{
  private:
    String menuName;
    Item* firstItem;
    String* itemNameList;
    Handlers::handler* itemHandlerList;
    int listSize;
    int leftPin, rightPin, selectPin;
    LiquidCrystal* lcd;
  public:
    Item* currentItem;
    static bool selectButtonPressed;

    Menu(String mName, LiquidCrystal& x, int arraySize, String* items, Handlers::handler* HandlersList);
    ~Menu();
    String getMenuName();
    void begin();
    void initMenu();
    void displayMenuSerial();
    void displayMenuLCD();
    int detectButtonPress();
    void clearMemoryForThisMenu();
};
