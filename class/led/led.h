#include <Arduino.h>

class LED
{
  private:
    int ledPin;
  
  public:
    LED(int pin);
    void blink(int ms);
    void blinkFast(int count);
};