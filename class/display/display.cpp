#include "display.h"
#include "icons.cpp"

DISPLAY_I2C::DISPLAY_I2C()
{
  oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
}

void DISPLAY_I2C::init()
{
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
  }

  oled.clearDisplay();
  oled.setCursor(0, 0);
}

void DISPLAY_I2C::clear()
{
  oled.clearDisplay();
}

void DISPLAY_I2C::println(int left, int top, int size, const String text)
{
  oled.setTextColor(WHITE);
  oled.setCursor(left, top);       // set position to display
  oled.setTextSize(size);         // set text size
  oled.println(text); // set text
}

void DISPLAY_I2C::drawPixel(int left, int top)
{
  oled.drawPixel(left, top, SSD1306_WHITE);
}

void DISPLAY_I2C::drawImage(int left, int top, const uint8_t icon[], int16_t width, int16_t height)
{
  oled.drawBitmap(left, top, icon, width, height, 1);
}

void DISPLAY_I2C::show()
{
  oled.display();
}