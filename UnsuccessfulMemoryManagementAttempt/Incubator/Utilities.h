#pragma once

#define BUZZER 16

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Utilities
{
  private:
    static bool buzzerFlag;
  public:
    static char temp[18];
    static char tempProfileName[9];
  
    static void stringToCharArray(String s,char *c);
    static void intToCharArray(long a,char* c);
    static int getNumberOfDigits(long a);
    static void resetCharacterArray();
    static void setBuzzerFlag(bool x);
    static void startBuzzer();
};
