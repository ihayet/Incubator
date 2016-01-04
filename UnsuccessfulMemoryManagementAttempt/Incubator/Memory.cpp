#include <EEPROM.h>
#include "Memory.h"
#include "Utilities.h"

int Memory::screenTimeoutTime;
unsigned long Memory::screenTimeoutStart;
int Memory::addressByteCounter;
Profiles* Memory::profileContainerStart;
int Memory::PROFILE_CONTAINER_SIZE;

Memory::Memory()
{    
  screenTimeoutTime = EEPROM.read(SCREEN_TIMEOUT_BYTE);
  
  addressByteCounter = MEMORY_START_BYTE;
  
  initProfileContainer();
}

void Memory::setScreenTimeoutStart()
{
  screenTimeoutStart = millis();
}

unsigned long Memory::getScreenTimeoutStart()
{
  return screenTimeoutStart;
}

int Memory:: getScreenTimeoutTime()
{
  return screenTimeoutTime;
}

void Memory::changeScreenTimeoutTime(int t)
{
  if(screenTimeoutTime != t)
  {
    screenTimeoutTime = t;
    EEPROM.write(SCREEN_TIMEOUT_BYTE, screenTimeoutTime);
    
    Utilities::startBuzzer();
    delay(100);
    Utilities::startBuzzer();
  }
}

Profiles* Memory::getProfileContainerStart()
{
  return profileContainerStart;
}

void Memory::initProfileContainer()
{
  profileContainerStart = new Profiles(NULL);
  
  PROFILE_CONTAINER_SIZE = EEPROM.read(MEMORY_SLOTS_BYTE);
  
  int i,j,k;
  Profiles* iterator = profileContainerStart;
  
  for(i=0;i<PROFILE_CONTAINER_SIZE;i++)
  {
    char tempProfileCharacterArray[9];
    
    //profile names
    
    for(j=0;j<8;j++)
    {
      tempProfileCharacterArray[j] = (char)EEPROM.read(addressByteCounter++);
    }
    
    tempProfileCharacterArray[j]='\0';
    String tempProfileName(tempProfileCharacterArray);
    
    iterator->setName(tempProfileName);
    
    //temperature
    iterator->setTemperature(EEPROM.read(addressByteCounter++));
    //humidity
    iterator->setHumidity(EEPROM.read(addressByteCounter++));
    
    iterator->setNextProfile();
    iterator = iterator->getNextProfile();
  }
  
  iterator->getPrevProfile()->setNextProfileToNULL();
}


void Memory::profilesToStringArray(String* s)
{
  int i = 0;
  Profiles* iterator = profileContainerStart;
  
  while(iterator!=NULL)
  {
    s[i] = iterator->getName();
    
    iterator = iterator->getNextProfile();
    i++;
  }
  
  const static PROGMEM String backString("Back");
  
  s[i] = backString;
}

int Memory::getProfileContainerSize()
{
  return PROFILE_CONTAINER_SIZE;
}
