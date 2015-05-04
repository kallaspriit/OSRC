#include "Owen.h"
#include "Config.h"
#include <max6675.h>

Owen::Owen() : 
  pid((double*) &temperature, (double*) &pidValue, (double*) &targetTemperature, PID_P, PID_I, PID_D, DIRECT)
{
  thermocouple = new MAX6675(THERMO_CLK, THERMO_CS, THERMO_DO);
}

void Owen::init() {
  pid.SetMode(AUTOMATIC);
}

void Owen::tick() {
  temperature = getTemperature();
  
  pid.Compute();
  DEBUG.println(pidValue);
  
  
  if (pidValue < 255) {
    setHeaterOn();
  }
  
  if (pidValue == 0) {
    setHeaterOff();
  }
}

void Owen::setTargetTemperature(float temperature) {
  targetTemperature = temperature; 
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
