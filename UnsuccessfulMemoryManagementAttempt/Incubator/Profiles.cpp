#include "Profiles.h"

Profiles* Profiles::currentProfile = NULL;

Profiles::Profiles(Profiles* p)
{
  prevProfile = p;
  nextProfile = NULL;
}

void Profiles::setName(String n)
{
  profileName = n;
}
void Profiles::setTemperature(long a)
{
  temperature = a;
}
void Profiles::setHumidity(long a)
{
  humidity = a;
}

String Profiles::getName()
{
  return profileName;
}
long Profiles::getTemperature()
{
  return temperature;
}
long Profiles::getHumidity()
{
  return humidity;
}

void Profiles::setNextProfile()
{
  nextProfile = new Profiles(this);
}
void Profiles::setNextProfileToNULL()
{
  nextProfile = NULL;
}
Profiles* Profiles::getNextProfile()
{
  return nextProfile;
}

Profiles* Profiles::getPrevProfile()
{
  return prevProfile;
}

void Profiles::setCurrentProfile(Profiles* p)
{
  currentProfile = p;
}

Profiles* Profiles::getCurrentProfile()
{
  return currentProfile;
}
