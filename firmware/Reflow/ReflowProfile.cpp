#include "ReflowProfile.h"
#include "Config.h"

ReflowProfile::ReflowProfile() {
  // timing
  profile.heatingElementTime = 40.0f;
  profile.preheatingTime = 80.0f;
  profile.soakingTime = 70.0f;
  profile.reflowTime = 30.0f;
  profile.reflowingTime = 5.0f;
  profile.coolingTime = 180.0f;
  
  // temperatures
  profile.heatingElementTemp = 80.0f;
  profile.preheatingTemp = 150.0f;
  profile.soakingTemp = 180.0f;
  profile.reflowTemp = 225.0f;
  profile.reflowingTemp = 225.0f;
  profile.coolingTemp = 50.0f;
  
  state = REFLOW_STATE_HEATING_ELEMENT;
}

void ReflowProfile::tick(float temp) {
  seconds = (int) ((millis()) / 1000);
  state = getStateByTime(seconds);
}

float ReflowProfile::getTargetTemperature(int seconds) {
  float time;
  float targetTemp;
  float previousTargetTemp;
  float calculatedTemp;
  int direction = 1;
  
  switch (getStateByTime(seconds)) {
    case REFLOW_STATE_HEATING_ELEMENT:
      time = profile.heatingElementTime;
      targetTemp = profile.heatingElementTemp;
      previousTargetTemp = profile.startTemp;
      break;
    case REFLOW_STATE_PREHEAT:
      time = profile.preheatingTime;
      targetTemp = profile.preheatingTemp;
      previousTargetTemp = profile.heatingElementTemp;
      break;
    case REFLOW_STATE_SOAK:
      time = profile.soakingTime;
      targetTemp = profile.soakingTemp;
      previousTargetTemp = profile.preheatingTemp;
      break;
    case REFLOW_STATE_REFLOW:
      time = profile.reflowTime;
      targetTemp = profile.reflowTemp;
      previousTargetTemp = profile.soakingTemp;
      break;
    case REFLOW_STATE_REFLOWING:
      time = profile.reflowingTime;
      targetTemp = profile.reflowingTemp;
      previousTargetTemp = profile.reflowTemp;
      break;
    case REFLOW_STATE_COOL:
      time = profile.coolingTime;
      targetTemp = profile.coolingTemp;
      previousTargetTemp = profile.reflowingTemp;
      direction = -1;
      break;  
  }

  calculatedTemp = previousTargetTemp + (100 / time * getStateSecondsByTime(seconds) / 100 * (targetTemp - previousTargetTemp));
  
  if (direction == 1) {
    return calculatedTemp < targetTemp ? calculatedTemp : targetTemp;
  } else {
    return calculatedTemp > targetTemp ? calculatedTemp : targetTemp;
  }
}

int ReflowProfile::getStateByTime(int seconds) {
  int time;
  if ((time = profile.heatingElementTime) > seconds) {
    return REFLOW_STATE_HEATING_ELEMENT;
  } else if ((time += profile.preheatingTime) > seconds) {
    return REFLOW_STATE_PREHEAT;
  } else if ((time += profile.soakingTime) > seconds) {
    return REFLOW_STATE_SOAK;
  } else if ((time += profile.reflowTime) > seconds) {
    return REFLOW_STATE_REFLOW;
  } else if ((time += profile.reflowingTime) > seconds) {
    return REFLOW_STATE_REFLOWING;
  } else if ((time += profile.coolingTime) > seconds) {
    return REFLOW_STATE_COOL;
  }
  
  return -1;
}

int ReflowProfile::getStateSecondsByTime(int seconds) {
  int time;
  if ((time = profile.heatingElementTime) > seconds) {
    return seconds;
  } else if ((time += profile.preheatingTime) > seconds) {
    return seconds - profile.heatingElementTime;
  } else if ((time += profile.soakingTime) > seconds) {
    return seconds - profile.heatingElementTime - profile.preheatingTime;
  } else if ((time += profile.reflowTime) > seconds) {
    return seconds - profile.heatingElementTime - profile.preheatingTime - profile.soakingTime;
  } else if ((time += profile.reflowingTime) > seconds) {
    return seconds - profile.heatingElementTime - profile.preheatingTime - profile.soakingTime - profile.reflowTime;
  } else if ((time += profile.coolingTime) > seconds) {
    return seconds - profile.heatingElementTime - profile.preheatingTime - profile.soakingTime - profile.reflowTime - profile.reflowingTime;
  }
  
  return 0;
}

void ReflowProfile::setStartTemp(float temp) {
  profile.startTemp = temp;
}
