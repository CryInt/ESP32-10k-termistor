void blink(int ms)
{
  digitalWrite(ONBOARD_LED,HIGH);
  delay(ms);
  digitalWrite(ONBOARD_LED,LOW);
}

void blinkFast(int count)
{
  int ms = 100;

  for (int i = 0; i < count; i++) {
    blink(ms);

    if (i != (count - 1)) {
      delay(ms);
    }
  }
}

void beep()
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

double getAnalogTemperatureValue()
{
  return analogRead(THERMISTOR_PIN);
}

double getTemperature()
{
  double adc = getAnalogTemperatureValue();
  adc = ADC_LUT[(int)adc];

  double Vout = adc * BOARD_VOLTAGE / MAX_AVAILABLE_ANALOG_VALUE_PIN;
  double Rt = DIVIDER_RESISTOR_VALUES * Vout / (BOARD_VOLTAGE - Vout);

  double T = 1 / (1 / REFERENCE_TEMPERATURE_IN_KELVIN_FOR_25 + log( Rt / REFERENCE_RESISTANCE_AT_25 ) / BETA); // Temperature in Kelvin
  
  return T - 273.15;
}
