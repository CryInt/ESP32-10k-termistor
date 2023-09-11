#include "led.h"

LED::LED(int pin)
{
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}

void LED::blink(int ms)
{
  digitalWrite(ledPin, HIGH);
  delay(ms);
  digitalWrite(ledPin, LOW);
}

void LED::blinkFast(int count)
{
  int ms = 100;

  for (int i = 0; i < count; i++) {
    LED::blink(ms);

    if (i != (count - 1)) {
      delay(ms);
    }
  }
}