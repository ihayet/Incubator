#pragma once

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define RESUME_BYTE 512                                //Byte in the EEPROM that decides if the incubator should resume from the previous settings - automatically resumes after power failure
#define MEMORY_TEMP_BYTE 513                           //Byte in the EEPROM that stores the temperature which is set by the user - to be used when the incubator resumes
#define MEMORY_HUM_BYTE 514                            //Byte in the EEPROM that stores the humidity which is set by the user - to be used when the incubator resumes
#define SOUND_OPTION_BYTE 515                          //Byte in the EEPROM that stores the sound option which is set by the user

#define RESUME 1                                       //When the incubator starts running the RESUME_BYTE is set to RESUME so that the incubator can automatically resume after power failure
#define DO_NOT_RESUME 2                                //When the incubator is stopped the RESUME_BYTE is set to DO_NOT_RESUME so that new settings can be set by the user

#define SOUND_ON 1                                     //When the user selects sound on from the sound option the SOUND_OPTION_BYTE is set to SOUND_ON
#define SOUND_OFF 2                                    //When the user selects sound off from the sound option the SOUND_OPTION_BYTE is set to SOUND_OFF

#define REDLED 5
#define GREENLED 6

class Memory
{
  private:

  public:
    static long setTemp;
    static long setHum;
    static long runningTemp;
    static long runningHum;
      
    Memory();
    static void initProfile();
    static void setResumeByte(int r);
    static int getResumeByte();
    static void setSoundByte(bool x);
};
