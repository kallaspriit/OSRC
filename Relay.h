#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class Relay {
  
  #define RELAY_OPEN 0
  #define RELAY_CLOSED 1
  
  public:
    Relay(int pin, int connectedLevel);
    
    void setOpen();
    void setClosed();
    boolean isOpen();
    
  private:
    int pin;
    int connectedLevel;
    int state;
    
    int getStateValue();
};

#endif;
