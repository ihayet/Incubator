#include <EEPROM.h>
#include "Memory.h"
#include "Utilities.h"

long Memory::setTemp = 0;
long Memory::setHum = 0;
long Memory::runningTemp;
long Memory::runningHum;

Memory::Memory()
{      
  initProfile();
}

void Memory::initProfile()
{
  if(EEPROM.read(SOUND_OPTION_BYTE)==SOUND_ON)
  {
    Utilities::setBuzzerFlag(true);
  }
  else if(EEPROM.read(SOUND_OPTION_BYTE)==SOUND_OFF)
  {
    Utilities::setBuzzerFlag(false);
  }
  
  if(EEPROM.read(RESUME_BYTE) == RESUME)
  {
    runningTemp = EEPROM.read(MEMORY_TEMP_BYTE);
    runningHum = EEPROM.read(MEMORY_HUM_BYTE);
    
    Utilities::targetTemp = runningTemp;
    Utilities::targetHum = runningHum;
    
    digitalWrite(GREENLED, HIGH);
    digitalWrite(REDLED, LOW);
    
    Utilities::runningFlag = true;
  }
  else if(EEPROM.read(RESUME_BYTE) == DO_NOT_RESUME)
  {
    setTemp = 0;
    setHum = 0;
    
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED,LOW);
    
    Utilities::runningFlag = false;
  }
}

void Memory::setResumeByte(int r)
{
  if(r==RESUME)
  {
    EEPROM.write(RESUME_BYTE,RESUME);
    EEPROM.write(MEMORY_TEMP_BYTE,setTemp);
    EEPROM.write(MEMORY_HUM_BYTE,setHum);
    
    runningTemp = setTemp;
    runningHum = setHum;
    
    Utilities::targetTemp = runningTemp;
    Utilities::targetHum = runningHum;
    
    Serial.println(F("EEPROM!"));
  }
  else if(r==DO_NOT_RESUME)
  {
    EEPROM.write(RESUME_BYTE,DO_NOT_RESUME);
  }
}

int Memory::getResumeByte()
{
  return EEPROM.read(RESUME_BYTE);
}

void Memory::setSoundByte(bool x)
{
  if(x==true)
  {
    if(EEPROM.read(SOUND_OPTION_BYTE)!=SOUND_ON)
    {
      EEPROM.write(SOUND_OPTION_BYTE,SOUND_ON);
    }
  }
  else if(x==false)
  {
    if(EEPROM.read(SOUND_OPTION_BYTE)!=SOUND_OFF)
    {
      EEPROM.write(SOUND_OPTION_BYTE,SOUND_OFF); 
    }
  }
}
