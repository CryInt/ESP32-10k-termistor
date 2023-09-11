#include <Arduino.h>

class THERMISTOR
{
  private:
    int thermistorPin;
    double getAnalogTemperatureValue();
  
  public:
    THERMISTOR(int pin);
    double getTemperature();
};