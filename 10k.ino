#include <WiFi.h>
#include <PubSubClient.h>

#include "config/config.h"

#include "class/beeper/beeper.cpp"
#include "class/led/led.cpp"
#include "class/thermistor/thermistor.cpp"
#include "class/display/display.cpp"

LED OnBoardLed(ONBOARD_LED);
BEEPER Sound(BEEPER_PIN);
THERMISTOR Thermistor(THERMISTOR_PIN);
DISPLAY_I2C Display;

#define mqtt_server "192.168.77.242"
#define mqtt_user ""
#define mqtt_password ""

#define temperature_topic "sensor/outdoor_water_temperature"

WiFiClient espClient;
PubSubClient client(espClient);

int Tick = 1;
double TemperatureArray[10];

void setup()
{
  Serial.begin(9600);

  Serial.println("RUN");

  Display.init();
  Display.clear();

  // connect to WiFi
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Sound.beep();
  OnBoardLed.blinkFast(3);
}

float average (double * array, int len)
{
  long sum = 0L;
  for (int i = 0; i < len; i++) {
    sum += array[i];
  }
  return ((float)sum) / len;
}

void loop()
{
  Serial.println(String("Tick: ") + Tick);

  double temperature = Thermistor.getTemperature();
  Serial.println(String("Received temperature: ") + temperature);

  TemperatureArray[Tick - 1] = temperature;

  String temperatureString = String(temperature, 2);

  double temperatureAverage = average(TemperatureArray, 10);
  Serial.println(String("Average temperature: ") + temperatureAverage);

  String temperatureStringAverage = String(temperatureAverage, 2);

  Display.clear();

  if (WiFi.status() == WL_CONNECTED) {
    Display.drawImage(90, 0, ICON_WIFI_HOTSPOT, ICON_WIFI_HOTSPOT_WIDTH, ICON_WIFI_HOTSPOT_HEIGHT);

    if (client.connected() == false) {
      client.setServer(mqtt_server, 1883);
      if (client.connect("ESP32WTClient", mqtt_user, mqtt_password)) {
        Serial.println("connected");
      } else {
        Serial.print("failed, rc=");
        Serial.println(client.state());
      }
    }
    else {
      Display.drawImage(111, 0, ICON_WIFI_HOTSPOT, ICON_WIFI_HOTSPOT_WIDTH, ICON_WIFI_HOTSPOT_HEIGHT);

      if (Tick >= 10) {
        client.publish(temperature_topic, String(temperatureStringAverage).c_str(), true);
        Serial.println(String("Publish temperature: ") + temperatureStringAverage);
        Tick = 0;
      }
    }
  }

  Display.println(0, 5, 1, temperatureString);
  Display.println(20, 30, 3, temperatureStringAverage);

  Display.show();

  OnBoardLed.blink(100);

  for(int i = 0; i < 10; i++) {
    Serial.print(TemperatureArray[i]);
    Serial.print(" | ");
  }
  Serial.println("");

  Tick++;

  delay(1000);
}
