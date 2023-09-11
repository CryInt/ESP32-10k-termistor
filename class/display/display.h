#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

class DISPLAY_I2C
{
  private:
    Adafruit_SSD1306 oled;
  
  public:
    DISPLAY_I2C();
    void init();
    void clear();
    void println(int left, int top, int size, const String text);
    void drawPixel(int left, int top);
    void drawImage(int left, int top, const uint8_t icon[], int16_t width, int16_t height);
    void show();
};