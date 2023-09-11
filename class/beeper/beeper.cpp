#include "beeper.h"

BEEPER::BEEPER(int pin)
{
  beeperPin = pin;
  pinMode(beeperPin, OUTPUT);
}

void BEEPER::beep()
{
  digitalWrite(beeperPin, HIGH);
  delay(100);
  digitalWrite(beeperPin, LOW);
}