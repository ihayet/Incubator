#include "Handlers.h"
#include "Utilities.h"
#include "Memory.h"
#include <DHT.h>

Menu* Handlers::currentMenu = NULL;
Menu** Handlers::menuContainer = NULL;
LiquidCrystal* Handlers::lcd = NULL;

DHT dht(DHTPIN, DHTTYPE);                                                      //Digital Humidity and Temperature sensor object

void Handlers::setCurrentMenu(Menu* m)
{
  currentMenu = m;
}

Menu* Handlers::getCurrentMenu()
{
  return currentMenu;
}

void Handlers::initMenuThroughHandlers(Menu** m, LiquidCrystal& x)
{
  menuContainer = m;

  currentMenu = menuContainer[0];

  lcd = &x;
}

void Handlers::backToMainMenu()
{
  Serial.println(F("Back To Main Menu - Handler"));

  currentMenu = menuContainer[0];
  delay(100);
}

//Main Menu - start
void Handlers::currentStatus()
{
  Serial.println(F("Current Status - Handler"));

  currentMenu = menuContainer[1];
  delay(100);
}

void Handlers::newSettings()
{
  Serial.println(F("New Settings"));

  currentMenu = menuContainer[2];
  delay(100);
}

void Handlers::sound()
{
  Serial.println(F("Sound - Handler"));

  currentMenu = menuContainer[3];
  delay(100);
}

void Handlers::rotation()
{
  int i;
  
  for(i=0;i<50;i++)
  {
    for(i=0;i<50;i++)
    {
      digitalWrite(BOX, HIGH);
      delay(1);
      digitalWrite(BOX, LOW);
      delay(2);
    }
    
    if(i<50)
    {
      delay(5000); 
    }
  }
  
  currentMenu = menuContainer[0];
  delay(100);
}

//Main Menu - end

//Current Status Menu - start

void Handlers::target()
{
  if (Utilities::runningFlag == false)
  {
    lcd->setCursor(0, 0);
    lcd->write("Not Running");
  }

  lcd->setCursor(0, 1);
  lcd->write("Temp:");

  Utilities::intToCharArray(Memory::runningTemp, Utilities::tempNumber);
  lcd->write(Utilities::tempNumber);

  lcd->write("C Hum:");

  Utilities::intToCharArray(Memory::runningHum, Utilities::tempNumber);
  lcd->write(Utilities::tempNumber);

  lcd->write("%");
}

void Handlers::currentTemperature()
{
  Utilities::temperature = dht.readTemperature();
  
  lcd->setCursor(0, 1);
  lcd->write("Temp:");

  Utilities::intToCharArray(Utilities::temperature, Utilities::tempNumber);
  lcd->write(Utilities::tempNumber);

  lcd->write("C");
  
  Utilities::updateTimeStart = millis();
}

void Handlers::currentHumidity()
{
  Utilities::humidity = dht.readHumidity();
  
  lcd->setCursor(0, 1);
  lcd->write("Hum:");

  Utilities::intToCharArray(Utilities::humidity, Utilities::tempNumber);
  lcd->write(Utilities::tempNumber);

  lcd->write("%");
  
  Utilities::updateTimeStart = millis();
}

void Handlers::stopExecution()
{
  Memory::setTemp = 0;
  Memory::setHum = 0;

  Memory::setResumeByte(2);

  currentMenu = menuContainer[0];

  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, HIGH);
  
  Utilities::runningFlag = false;
}

//Current Status Menu - end

//New Settings Menu - start

void Handlers::temp()
{  
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->write("Temp: ");
  lcd->setCursor(0, 1); 
  
  Utilities::intToCharArray(Memory::setTemp,Utilities::tempNumber);
  
  lcd->write(Utilities::tempNumber);
  lcd->write("C");
}

void Handlers::hum()
{  
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->write("Hum: ");
  lcd->setCursor(0, 1);
  
  Utilities::intToCharArray(Memory::setHum,Utilities::tempNumber);
  
  lcd->write(Utilities::tempNumber);
  lcd->write("%");
}

void Handlers::start()
{
  Memory::setResumeByte(1);
  Memory::initProfile();

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->write("All the best");

  delay(2000);

  currentMenu = menuContainer[0];

  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);
  
  Utilities::runningFlag = true;
}

//New Settings Menu - end

//Sound Menu - start

void Handlers::soundOn()
{
  Utilities::setBuzzerFlag(true);
  Memory::setSoundByte(true);

  currentMenu = menuContainer[0];
  delay(100);
}

void Handlers::soundOff()
{
  Utilities::setBuzzerFlag(false);
  Memory::setSoundByte(false);

  currentMenu = menuContainer[0];
  delay(100);
}

//Sound Menu - end
