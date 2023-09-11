#include "config.h"
#include "lut.h"
#include "functions.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 1);

void setup()
{
  Serial.begin(9600);

  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(THERMISTOR_PIN, INPUT);

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000); // wait two seconds for initializing

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

  String temperatureString = String(temperature,2);

  oled.clearDisplay(); // clear display
  oled.setCursor(0, 0);

  oled.setTextSize(2);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 20);       // set position to display
  oled.println(temperatureString + " " + (char)247 + "C"); // set text

  //int startnum = 320; 
  //for (int i = startnum; i < startnum+20; i++)  {
  //  oled.print((char)i); 
  //}

  oled.display();              // display on OLED

  blink(100);

  delay(1000);
}
