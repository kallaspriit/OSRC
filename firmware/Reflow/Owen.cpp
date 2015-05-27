#include "Owen.h"
#include "Config.h"
#include <max6675.h>

Owen::Owen() : 
  pid((double*) &temperature, (double*) &pidValue, (double*) &targetTemperature, PID_P, PID_I, PID_D, DIRECT)
{
  thermocouple = new MAX6675(THERMO_CLK, THERMO_CS, THERMO_DO);
  profile = ReflowProfile();
}

void Owen::init() {
  pid.SetOutputLimits(0, 1);
  pid.SetMode(AUTOMATIC);
  pid.SetTunings(PID_P, PID_I, PID_D);
  
}

void Owen::tick() {
  temperature = getTemperature();
  profile.setStartTemp(temperature);
  
  profile.tick(temperature);
  
  setTargetTemperature(profile.getTargetTemperature(profile.seconds + 10));
  
  pid.Compute();
  
  pidValue == 1 ? setHeaterOn() : setHeaterOff();
  
  if (profile.state == REFLOW_STATE_COOL) {
    setHeaterOff();
  }
}

ReflowProfile Owen::getProfile() {
  return profile;
}

void Owen::setTargetTemperature(float temperature) {
  targetTemperature = temperature; 
}

float Owen::getTargetTemperature() {
  return targetTemperature;
}

float Owen::getTemperature() {
  return (float) thermocouple->readCelsius(); 
}

void Owen::setHeaterOn() {
  heaterState = true;
}

void Owen::setHeaterOff() {
  heaterState = false;
}

boolean Owen::isHeaterOn() {
  return heaterState == true;
}

float Owen::getPidValue() {
  return pidValue;
}
