#include <LiquidCrystal.h>
#include "Menu.h"
#include "Utilities.h"
#include "Memory.h"

bool Menu::selectButtonPressed = false;
bool Menu::menuIn = false;

Menu::Menu(String mName, LiquidCrystal& x, int arraySize, String* items, Handlers::handler* HandlersList)
{
  Serial.println("Started");

  menuName = mName;

  lcd = &x;

  listSize = arraySize;
  itemNameList = items;
  itemHandlerList = HandlersList;

  firstItem = new Item(NULL);
  currentItem = firstItem;

  initMenu();
}

String Menu::getMenuName()
{
  return menuName;
}

void Menu::begin()
{

}

void Menu::initMenu()
{
  int i;
  Item* iterator = firstItem;

  for (i = 0; i < listSize; i++)
  {
    iterator->setName(itemNameList[i]);
    iterator->setHandler(itemHandlerList[i]);
    
    iterator->createNextItem();
    iterator = iterator->getNextItem();
  }
  
  iterator->getPreviousItem()->setNextItem(NULL);
}

void Menu::displayMenuSerial()
{
  Item* iterator = firstItem;

  while (iterator != NULL)
  {
    Serial.print(iterator->getID());
    Serial.print(" ");
    Serial.println(iterator->getName());

    iterator = iterator->getNextItem();
  }

  Serial.println();
}

void Menu::displayMenuLCD()
{
  if(menuIn == true)
  {
    currentItem = firstItem;
    menuIn = false;
  }
  
  Utilities::stringToCharArray(currentItem->getName(),Utilities::temp);
  
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->write(Utilities::temp);
  
  if(currentItem->getName() == "Target:" || currentItem->getName() == "Current Temp:" || currentItem->getName() == "Current Hum:" || currentItem->getName() == "Temp: " || currentItem->getName() == "Hum: ")            //For the "Current Status menu", the item's handler will be called automatically without having to press the "SELECT" button so that the current status is shown in the lower row with the "Current Status menu" items (e.g "Profile name", "Current temp", ...) shown in the upper row
  {
    currentItem->getHandler()(); 
  }
}

int Menu::detectButtonPress()
{
  if (digitalRead(LEFT) == HIGH)
  {
    delay(100);
        
    if(currentItem->getName() == "Temp: ")
    {
      Memory::setTemp--;
      displayMenuLCD();
      delay(200);
    }
    else if(currentItem->getName() == "Hum: ")
    {
      Memory::setHum--;
      displayMenuLCD();
      delay(200);
    }
    else if (currentItem->getPreviousItem() != NULL)
    {
      Utilities::startBuzzer();
      currentItem = currentItem->getPreviousItem();
      displayMenuLCD();
      delay(500);
    }
    
    digitalWrite(BRIGHTNESS, HIGH);
    
    return 1;
  }
  else if (digitalRead(RIGHT) == HIGH)
  {
    delay(100);
        
    if(currentItem->getName() == "Temp: ")
    {
      Memory::setTemp++;
      displayMenuLCD();
      delay(200);
    }
    else if(currentItem->getName() == "Hum: ")
    {
      Memory::setHum++;
      displayMenuLCD();
      delay(200);
    }
    else if (currentItem->getNextItem() != NULL)
    {
      Utilities::startBuzzer();
      currentItem = currentItem->getNextItem();
      displayMenuLCD();
      delay(500);
    }
    
    digitalWrite(BRIGHTNESS, HIGH);
    
    return 2;
  }
  else if (digitalRead(SELECT) == HIGH)
  {
    delay(100);
    
    Utilities::startBuzzer();
        
    if(menuName == "Main menu" && currentItem->getName()!= "Rotation")
    {
      menuIn = true;
    }
    
    if(currentItem->getName() == "Temp: ")
    {
      currentItem = currentItem->getNextItem();
      displayMenuLCD();
      
      delay(200);
    }
    else if(currentItem->getName() == "Hum: ")
    {
      currentItem = currentItem->getNextItem();      
      displayMenuLCD();
      
      delay(200);
    }
    else
    {
      if(menuName == "New Settings menu" && currentItem->getName() == "Back")
      {
        if(Utilities::runningFlag == false)
        {
           Memory::setTemp = 0;
           Memory::setHum = 0;
           
           Utilities::targetTemp = Memory::setTemp;
           Utilities::targetHum = Memory::setHum;
        }
      }
      
      selectButtonPressed = true;
      currentItem->getHandler()();    
      delay(200);
    }
    
    digitalWrite(BRIGHTNESS, HIGH);
    
    return 3;
  }
  
  if(currentItem->getName() == "Current Temp:" || currentItem->getName() == "Current Hum:")
  {
    if(millis() - Utilities::updateTimeStart > 1000)
    {
      displayMenuLCD(); 
    }
  }
  
  return 4;
}
