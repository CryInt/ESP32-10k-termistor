#include "config.h"
#include "functions.h"

void setup()
{
  Serial.begin(9600);

  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(THERMISTOR_PIN, INPUT);

  Serial.println("RUN");
  beep();
  blinkFast(3);
}

void loop()
{
  Serial.println("Tick!");
  
  //blinkFast(3);

  double temperature = getTemperature();
  Serial.println(temperature);

  delay(1000);
}
