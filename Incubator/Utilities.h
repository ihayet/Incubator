#pragma once

#define LEFT 4
#define RIGHT 2
#define SELECT 3

#define FAN 18
#define BOX 17
#define LIGHT 19

#define REDLED 5
#define GREENLED 6

#define BUZZER 16

#define DHTPIN A0                                //analog pin that is connected to the Digital Humidity and Temperature Sensor
#define DHTTYPE DHT11                            //type of the Digital Humidity and Temperature Sensor

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Utilities
{
  private:
    
  public: 
    static char temp[18];
    static char tempNumber[4];
    static bool runningFlag;
    static unsigned long updateTimeStart;
    
    static bool buzzerFlag;
    
    static long temperature;
    static long humidity;
    static long targetTemp;
    static long targetHum;
  
    static void stringToCharArray(String s,char *c);
    static void intToCharArray(long a,char* c);
    static int getNumberOfDigits(long a);
    static void resetCharacterArray(char* c,int len);
    static void setBuzzerFlag(bool x);
    static void startBuzzer();
    static void controlSystem();
};
