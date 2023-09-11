#include <Arduino.h>

class BEEPER
{
  private:
    int beeperPin;
  
  public:
    BEEPER(int pin);
    void beep();
};