#pragma once

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Profiles.h"

#define SCREEN_TIMEOUT_BYTE 511

//Profile Memory - start

#define MAXIMUM_PROFILE_NUMBER 2

#define MEMORY_SLOTS_BYTE 512
#define MEMORY_START_BYTE 513

#define UNIT_SIZE 10

//Profile Memory - end
 
class Memory
{
  private:
    static int screenTimeoutTime;
    static unsigned long screenTimeoutStart;
    static int addressByteCounter;
    static int PROFILE_CONTAINER_SIZE;
    static Profiles* profileContainerStart;
  public:
    Memory();
    static void setScreenTimeoutStart();
    static unsigned long getScreenTimeoutStart();
    static int getScreenTimeoutTime();
    static void changeScreenTimeoutTime(int t);
    static Profiles* getProfileContainerStart();
    void initProfileContainer();
    void profilesToStringArray(String* s);
    static int getProfileContainerSize();
};
