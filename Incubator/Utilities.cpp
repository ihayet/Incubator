#include "Utilities.h"
#include <math.h>
#include <DHT.h>

bool Utilities::buzzerFlag = false;
char Utilities::temp[18];
char Utilities::tempNumber[4];
bool Utilities::runningFlag = false;
long Utilities::temperature;
long Utilities::humidity;
unsigned long Utilities::updateTimeStart;
long Utilities::targetTemp;
long Utilities::targetHum;

DHT dhtUtil(DHTPIN, DHTTYPE);                                                                                  //Digital Humidity and Temperature sensor object                                      

void Utilities::stringToCharArray(String s, char* c)
{
  resetCharacterArray(c,18);
  
  int i;

  for (i = 0; i <= s.length(); i++)
  {
    *(c+i) = s[i];
  }
}

void Utilities::intToCharArray(long a, char* c)
{  
  resetCharacterArray(c,4);
  
  int numberOfDigits = Utilities::getNumberOfDigits(a);
  int i, digit;

  for (i = numberOfDigits - 1; i >= 0; i--)
  {
    digit = a % 10;
    a = a / 10;

    *(c + i) = digit + 48; 
  }
  *(c+numberOfDigits) = '\0';
}

int Utilities::getNumberOfDigits(long a)
{
  double x = (double)a * 1.0;

  int numberOfDigits = log10(x) + 1;

  return numberOfDigits;
}

void Utilities::resetCharacterArray(char* c,int len)
{
  int i;
  
  for(i=0;i<len;i++)
  {
    *(c+i) = '\0';
  }
}

void Utilities::setBuzzerFlag(bool x)
{
  buzzerFlag = x;
}

void Utilities::startBuzzer()
{
  if(buzzerFlag == true)
  {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, LOW); 
  }
}

void Utilities::controlSystem()
{
  if(runningFlag == true)
  {
    temperature = dhtUtil.readTemperature();
    humidity = dhtUtil.readHumidity();
    
    if(temperature > targetTemp)
    {
      delay(500);
      digitalWrite(LIGHT, HIGH);
      delay(500);
      digitalWrite(FAN, HIGH);
      delay(500);
    }
    else if(temperature < targetTemp)
    {
      delay(100);
      digitalWrite(LIGHT, LOW);
      delay(100);
      digitalWrite(FAN, LOW);
      delay(100);
    }
    
    if(humidity > targetHum)
    {
      delay(500);
      digitalWrite(FAN, HIGH);
      delay(500);
    }
    else
    {
      if(temperature <= targetTemp)
      {
        delay(100);
        digitalWrite(FAN, LOW); 
        delay(100);
      }
    }
  }
}
