#include <LiquidCrystal.h>
#include "Menu.h"
#include "Utilities.h"
#include "Memory.h"

bool Menu::selectButtonPressed = false;

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

Menu::~Menu()
{
  
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
  Utilities::stringToCharArray(currentItem->getName(),Utilities::temp);
  
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->write(Utilities::temp);
  
  if((menuName == "Current Status menu" || menuName == "View Profiles menu") && currentItem->getName() != "Stop" && currentItem->getName() != "Back")            //For the "Current Status menu", the item's handler will be called automatically without having to press the "SELECT" button so that the current status is shown in the lower row with the "Current Status menu" items (e.g "Profile name", "Current temp", ...) shown in the upper row
  {
    currentItem->getHandler()();
  }
}

int Menu::detectButtonPress()
{
  if (digitalRead(LEFT) == HIGH)
  {
    delay(100);
  
    if (currentItem->getPreviousItem() != NULL)
    {
      Utilities::startBuzzer();
      currentItem = currentItem->getPreviousItem();
      displayMenuLCD();
      delay(500);
    }
    
    digitalWrite(BRIGHTNESS, HIGH);
    Memory::setScreenTimeoutStart();
  }
  else if (digitalRead(RIGHT) == HIGH)
  {
    delay(100);
  
    if (currentItem->getNextItem() != NULL)
    {
      Utilities::startBuzzer();
      currentItem = currentItem->getNextItem();
      displayMenuLCD();
      delay(500);
    }
    
    digitalWrite(BRIGHTNESS, HIGH);
    Memory::setScreenTimeoutStart();
  }
  else if (digitalRead(SELECT) == HIGH)
  {
    delay(100);
    
    Utilities::startBuzzer(); 
    
    if(menuName == "View Profiles menu" && currentItem->getName() != "Back")
    {      
      char temp[currentItem->getName().length()+1];
      Utilities::stringToCharArray(currentItem->getName(),temp);
      
      lcd->clear();
      lcd->setCursor(0, 0);
      lcd->write(temp);
      
      lcd->setCursor(2, 1);
      lcd->write("Yes");
      lcd->setCursor(12, 1);
      lcd->write("No");
      
      while(true)
      {
        if(digitalRead(LEFT)==HIGH)
        {
          lcd->clear();
          lcd->setCursor(0, 0);
          lcd->write(temp);
          lcd->write(" selected");
          lcd->setCursor(0, 1);
          lcd->write("All the best");
          
          delay(5000);
          
          break;
        }
        else if(digitalRead(RIGHT)==HIGH)
        {
          delay(100);
          
          break;
        }
      }
    }
    else
    {
      selectButtonPressed = true;
      currentItem->getHandler()();
    }   
    
    delay(200);
    
    digitalWrite(BRIGHTNESS, HIGH);
    Memory::setScreenTimeoutStart();
  }
}

void Menu::clearMemoryForThisMenu()
{
  Item* iterator = firstItem;
  Item* temp;
  
  while(iterator!=NULL)
  {
    temp = iterator->getNextItem();
    free(iterator);
    iterator = temp;
  }
}
