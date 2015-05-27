#ifndef REFLOWPROFILE_H
#define REFLOWPROFILE_H

#include <Arduino.h>

/*
* Temperature (Degree Celcius)                 Magic Happens Here!
* 245-|                                               x  x  
*     |                                            x        x
*     |                                         x              x
*     |                                      x                    x
* 200-|                                   x                          x
*     |                              x    |                          |   x   
*     |                         x         |                          |       x
*     |                    x              |                          |
* 150-|               x                   |                          |
*     |             x |                   |                          |
*     |           x   |                   |                          | 
*     |         x     |                   |                          | 
*     |       x       |                   |                          | 
*     |     x         |                   |                          |
*     |   x           |                   |                          |
* 30 -| x             |                   |                          |
*     |<  60 - 90 s  >|<    90 - 120 s   >|<       90 - 120 s       >|
*     | Preheat Stage |   Soaking Stage   |       Reflow Stage       | Cool
*  0  |_ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
*                                                                Time (Seconds)
*/

class ReflowProfile {
  
//  #define REFLOW_STATE_HEATING_ELEMENT 0
  #define REFLOW_STATE_PREHEAT 1
  #define REFLOW_STATE_SOAK 2
  #define REFLOW_STATE_REFLOW 3
  #define REFLOW_STATE_REFLOWING 4
  #define REFLOW_STATE_COOL 5
  
  public:
    struct Profile {
      // timing
 //     float heatingElementTime;
      float preheatingTime;
      float soakingTime;
      float reflowTime;
      float reflowingTime;
      float peakTime;
      float coolingTime;
      
      // temperatures
      float startTemp;
//      float heatingElementTemp;
      float preheatingTemp;
      float soakingTemp;
      float reflowTemp;
      float reflowingTemp;
      float coolingTemp;
    };
    
    ReflowProfile();
    void init();
    void tick(float temp);
    float getTargetTemperature(int seconds);
    int getStateByTime(int seconds);
    int getStateSecondsByTime(int seconds);
    void setStartTemp(float temp);
    
    int state;
    int seconds;
    
  protected:
    void calculateState(float temp);
    
    Profile profile;    
};

#endif
