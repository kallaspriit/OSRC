#include "Config.h"
#include "ReflowProfile.h"
#include "Owen.h"
#include "Relay.h"

#include <PID_v1.h>
#include <max6675.h>
#include <SPI.h>

Owen owen = Owen();
Relay relay = Relay(RELAY_PIN, LOW);

void setup() {
  DEBUG.begin(9600);
  owen.setTargetTemperature(50);
  owen.init(); 
}

void loop() {  
  owen.tick();
  owen.isHeaterOn() ? relay.setClosed() : relay.setOpen();
  //DEBUG.println(owen.isHeaterOn());
  DEBUG.println(owen.getTemperature());

  delay(500);
}
