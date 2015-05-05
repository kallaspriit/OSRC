#include "ReflowProfile.h"
#include "Config.h"

ReflowProfile::ReflowProfile() {
  // timing
  profile.timeMultiplier = 3.0f;
  profile.preheatTime = 4.0f * 60.0f;
  profile.soakingTime = 1.5f * 60.0f;
  profile.reflowTime = 1.5f * 60.0f;
  profile.peakTime = 20;
  profile.coolingTime = 2.0f * 60.0f;
  
  // temperatures
  profile.startTemp = 0;
  profile.preheatTemp = 150.0f;
  profile.soakingTemp = 170.0f;
  profile.reflowTemp = 240.0f;
  profile.coolingTemp = 100.0f;
}

float ReflowProfile::getTargetTemperature(int seconds) {
  float t1, t2;
  float progress;
  
  if (seconds < getPreheatTime()) {
    t1 = profile.startTemp;
    t2 = profile.preheatTemp;
    progress = seconds / getPreheatTime();
  } else if (seconds < getPreheatTime() + getSoakingTime()) {
    t1 = profile.preheatTemp;
    t2 = profile.soakingTemp;
    progress = (seconds - getPreheatTime()) / getSoakingTime();
  } else if (seconds < getPreheatTime() + getSoakingTime() + getReflowTime()) {
    t1 = profile.soakingTemp;
    t2 = profile.reflowTemp;
    progress = (seconds - getPreheatTime() - getSoakingTime()) / getReflowTime();
  } else if (seconds < getPreheatTime() + getSoakingTime() + getReflowTime() + getPeakTime()) {
    t1 = profile.reflowTemp;
    t2 = profile.reflowTemp;
    progress = (seconds - getPreheatTime() - getSoakingTime() - getReflowTime()) / getPeakTime();
  } else {
    t1 = profile.reflowTemp;
    t2 = profile.coolingTemp;
    progress = (seconds - getPreheatTime() - getSoakingTime() - getReflowTime() - getPeakTime()) / getCoolingTime();
  }

  if (progress > 1.0f) {
    return -1;
  }
  
  return t1 + (float)(t2 - t1) * progress; 
}

float ReflowProfile::getPreheatTime() {
  return profile.preheatTime;
}

float ReflowProfile::getSoakingTime() {
  return profile.soakingTime;
}

float ReflowProfile::getReflowTime() {
  return profile.reflowTime;
}

float ReflowProfile::getPeakTime() {
  return profile.peakTime;
}

float ReflowProfile::getCoolingTime() {
  return profile.coolingTime;
}

float ReflowProfile::getPreheatTemp() {
  return profile.preheatTemp;
}

float ReflowProfile::getSoakingTemp() {
  return profile.soakingTemp;
}

float ReflowProfile::getReflowTemp() {
  return profile.reflowTemp;
}

float ReflowProfile::getCoolingTemp() {
  return profile.coolingTemp;
}
