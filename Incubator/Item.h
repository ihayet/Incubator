#pragma once

#include "Handlers.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Item
{
  private:
    int id;
    String itemName;
    Item* previousItem;
    Item* nextItem;
    Handlers::handler itemHandler;
  public:
    static int itemCounter;

    Item(Item* prev);
    void setName(String n);
    void setHandler(Handlers::handler h);
    int getID();
    String getName();
    Handlers::handler getHandler();
    void createNextItem();
    void setNextItem(Item* i);
    Item* getNextItem();
    Item* getPreviousItem();
};
