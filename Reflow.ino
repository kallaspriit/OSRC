#include "Config.h"
#include "ReflowProfile.h"
#include "Owen.h"
#include "Relay.h"
#include "ReflowProfile.h"

#include <PID_v1.h>
#include <max6675.h>
#include <SPI.h>

Owen owen = Owen();
Relay relay = Relay(RELAY_PIN, LOW);
ReflowProfile profile = ReflowProfile();

int seconds = 0;

void setup() {
  DEBUG.begin(9600);
  owen.init(); 
}

void loop() {  
  
  if (owen.getTemperature() < 60) {
    DEBUG.println(owen.getTemperature());
    
    owen.setTargetTemperature(60);
    owen.tick();
    owen.isHeaterOn() ? relay.setClosed() : relay.setOpen();
    delay(1000);
  } else {
  
    seconds += 1;
  
  
    DEBUG.print(seconds);
    DEBUG.print(": ");
    DEBUG.print(profile.getTargetTemperature(seconds));  
    DEBUG.print(": ");
    owen.setTargetTemperature(profile.getTargetTemperature(seconds));
    
    //owen.getTargetTemperature
    
    owen.tick();
    owen.isHeaterOn() ? relay.setClosed() : relay.setOpen();
    
    
    DEBUG.print(": ");
    //DEBUG.println(owen.isHeaterOn());
    DEBUG.println(owen.getTemperature());
  
    delay(1000);
    
  }
  
  
  
  /*
  DEBUG.print(seconds);
  DEBUG.print(",");
  
  owen.setTargetTemperature(100);
  owen.tick();
  owen.isHeaterOn() ? relay.setClosed() : relay.setOpen();
  
  
  //DEBUG.print(": ");
  //DEBUG.println(owen.isHeaterOn());
 
  DEBUG.print(owen.isHeaterOn());
  DEBUG.print(",");
  
  DEBUG.println(owen.getTemperature());
 
  seconds++;
  
  delay(1000);*/
}
