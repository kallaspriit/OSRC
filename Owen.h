#ifndef OWEN_H
#define OWEN_H

#include <Arduino.h>
#include <PID_v1.h>

class MAX6675;

class Owen {
  
  public:
    Owen();
    
    void init();
    float getTemperature();
    void calculateTemperature();
    void tick();
    void setHeaterOn();
    void setHeaterOff();
    boolean isHeaterOn();
    void setTargetTemperature(float temperature);
    
  protected:
    boolean heaterState;
    float temperature;
    float targetTemperature;
    PID pid;
    float pidValue;
    MAX6675 *thermocouple;
};

#endif
