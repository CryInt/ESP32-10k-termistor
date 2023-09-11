#include <WiFi.h>

#include "config/config.h"

#include "class/beeper/beeper.cpp"
#include "class/led/led.cpp"
#include "class/thermistor/thermistor.cpp"
#include "class/display/display.cpp"

LED OnBoardLed(ONBOARD_LED);
BEEPER Sound(BEEPER_PIN);
THERMISTOR Thermistor(THERMISTOR_PIN);
DISPLAY_I2C Display;

void setup()
{
  Serial.begin(9600);

  Serial.println("RUN");

  Display.init();
  Display.clear();

  // connect to WiFi
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  // ====

  Sound.beep();
  OnBoardLed.blinkFast(3);
}

void loop()
{
  Serial.println("Tick!");

  double temperature = Thermistor.getTemperature();
  Serial.println(temperature);

  String temperatureString = String(temperature, 2);

  Display.clear();

  if (WiFi.status() == WL_CONNECTED) {
    Display.drawImage(111, 0, ICON_WIFI_HOTSPOT, ICON_WIFI_HOTSPOT_WIDTH, ICON_WIFI_HOTSPOT_HEIGHT);
  }

  Display.println(20, 30, 3, temperatureString);

  Display.show();

  OnBoardLed.blink(100);

  delay(1000);
}
