#include "Relay.h"
#include "Config.h"

Relay::Relay(int pin, int connectedLevel) : 
  pin(pin),
  connectedLevel(connectedLevel),
  state(RELAY_OPEN)
{
  pinMode(pin, OUTPUT);
  setOpen();
}

void Relay::setOpen() {
  state = RELAY_OPEN;
  digitalWrite(pin, getStateValue());
}

void Relay::setClosed() {
  state = RELAY_CLOSED;
  digitalWrite(pin, getStateValue());
}

int Relay::getStateValue() {
  if (state == RELAY_CLOSED) {
    return connectedLevel == HIGH ? LOW : HIGH;
  } else {
    return connectedLevel == HIGH ? HIGH : LOW;
  }
}

boolean Relay::isOpen() {
  return state == RELAY_OPEN;
}
