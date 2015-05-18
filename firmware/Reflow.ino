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

int seconds = 1;

long previousMillis = 0; 

void setup() {
  DEBUG.begin(9600);
  owen.init(); 
}

void loop() {
  if (millis() - previousMillis > 1000) {
    previousMillis = millis();
      
    owen.tick();
    owen.isHeaterOn() ? relay.setClosed() : relay.setOpen();
    
    
    DEBUG.print(seconds);
    DEBUG.print("\t");
    DEBUG.print(owen.getProfile().state);
    DEBUG.print("\t");
    DEBUG.print(owen.getProfile().getStateSecondsByTime(owen.getProfile().seconds));
    DEBUG.print("\t");
    DEBUG.print(owen.getTemperature());
    DEBUG.print("\t");
    DEBUG.print(owen.getProfile().getTargetTemperature(owen.getProfile().seconds));
    DEBUG.print("\t");
    DEBUG.print(owen.getProfile().getTargetTemperature(owen.getProfile().seconds + 30));
    DEBUG.print("\t");
    DEBUG.print(owen.getPidValue());
    DEBUG.print("\t");
    DEBUG.println(owen.isHeaterOn() * 255);

  
  //delay(1000);
  seconds++;
  
  
  }
  
}
