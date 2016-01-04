#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Profiles
{
  private:  
    String profileName;
    long temperature, humidity;
    Profiles *prevProfile, *nextProfile;
    static Profiles *currentProfile;
  public:
    Profiles(Profiles* p);
    void setName(String n);
    void setTemperature(long a);
    void setHumidity(long a);
    String getName();
    long getTemperature();
    long getHumidity();
    
    void setNextProfile();
    void setNextProfileToNULL();
    Profiles* getNextProfile();
    Profiles* getPrevProfile();
    
    static void setCurrentProfile(Profiles* p);
    static Profiles* getCurrentProfile();
};
