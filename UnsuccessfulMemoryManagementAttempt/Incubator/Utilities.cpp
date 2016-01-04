#include "Utilities.h"
#include <math.h>

bool Utilities::buzzerFlag = false;
char Utilities::temp[18];
char Utilities::tempProfileName[9];

void Utilities::stringToCharArray(String s, char* c)
{
  resetCharacterArray();
  
  int i;

  for (i = 0; i <= s.length(); i++)
  {
    *(c+i) = s[i];
  }
}

void Utilities::intToCharArray(long a, char* c)
{
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

void Utilities::resetCharacterArray()
{
  int i;
  
  for(i=0;i<18;i++)
  {
    temp[i] = '\0';
  }
  
  for(i=0;i<9;i++)
  {
    tempProfileName[i] = '\0';
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
