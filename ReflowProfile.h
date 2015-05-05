#ifndef REFLOWPROFILE_H
#define REFLOWPROFILE_H

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
  
  #define REFLOW_STATE_OFF 0
  #define REFLOW_STATE_PREHEAT 1
  #define REFLOW_STATE_SOAK 2
  #define REFLOW_STATE_REFLOW 3
  #define REFLOW_STATE_PEAK 4
  #define REFLOW_STATE_COOL 5
  
  public:
    struct Profile {
      // timing
      float timeMultiplier;
      float preheatTime;
      float soakingTime;
      float reflowTime;
      float peakTime;
      float coolingTime;
      
      // temperatures
      float startTemp;
      float preheatTemp;
      float soakingTemp;
      float reflowTemp;
      float coolingTemp;
    };
    
    ReflowProfile();
    void init();
    void setState(int state);
    float getTargetTemperature(int seconds);
    float getPreheatTime();
    float getSoakingTime();
    float getReflowTime();
    float getPeakTime();
    float getCoolingTime();
    float getStartTemp();
    float getPreheatTemp();
    float getSoakingTemp();
    float getReflowTemp();
    float getCoolingTemp();
    
  protected:
    Profile profile;
};

#endif
