#include "thermistor.h"
#include "lut.h"

THERMISTOR::THERMISTOR(int pin)
{
  thermistorPin = pin;
  pinMode(thermistorPin, INPUT);
}

double THERMISTOR::getAnalogTemperatureValue()
{
  return analogRead(thermistorPin);
}

double THERMISTOR::getTemperature()
{
  double adc = THERMISTOR::getAnalogTemperatureValue();
  adc = ADC_LUT[(int)adc];

  double Vout = adc * BOARD_VOLTAGE / MAX_AVAILABLE_ANALOG_VALUE_PIN;
  double Rt = DIVIDER_RESISTOR_VALUES * Vout / (BOARD_VOLTAGE - Vout);

  double T = 1 / (1 / REFERENCE_TEMPERATURE_IN_KELVIN_FOR_25 + log( Rt / REFERENCE_RESISTANCE_AT_25 ) / BETA); // Temperature in Kelvin
  
  return T - 273.15;
}