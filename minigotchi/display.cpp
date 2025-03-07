/**
 * display.cpp: handles display support for the d-duino board using SSD1306Wire.
 */

#include "display.h"
#ifdef USE_SSD1306WIRE
  // Only one global pointer is needed in this configuration.
  SSD1306Wire *ssd1306_dduino_display = nullptr;
#else
  // Other display objects (unused in this configuration)
  Adafruit_SSD1306 *ssd1306_adafruit_display = nullptr;
  Adafruit_SSD1305 *ssd1305_adafruit_display = nullptr;
  U8G2_SSD1306_128X64_NONAME_F_SW_I2C *ssd1306_ideaspark_display = nullptr;
  U8G2_SH1106_128X64_NONAME_F_SW_I2C *sh1106_adafruit_display = nullptr;
#endif

Display::~Display() {
#ifdef USE_SSD1306WIRE
  if (ssd1306_dduino_display) {
    delete ssd1306_dduino_display;
  }
#else
  if (ssd1306_adafruit_display) {
    delete ssd1306_adafruit_display;
  }
  if (ssd1305_adafruit_display) {
    delete ssd1305_adafruit_display;
  }
  if (ssd1306_ideaspark_display) {
    delete ssd1306_ideaspark_display;
  }
  if (sh1106_adafruit_display) {
    delete sh1106_adafruit_display;
  }
#endif
}

void Display::startScreen() {
#ifdef USE_SSD1306WIRE
  // Create and initialize the SSD1306Wire display.
  // The constructor parameters for SSD1306Wire are:
  //   (uint8_t address, int sda, int scl, OLEDDISPLAY_GEOMETRY g, HW_I2C i2cBus, long frequency)
  // GEOMETRY_128_64 and I2C_ONE are defined as int constants, so we cast them to the required enum types.
  ssd1306_dduino_display = new SSD1306Wire(0x3c, D1, D2,
    static_cast<OLEDDISPLAY_GEOMETRY>(GEOMETRY_128_64),
    static_cast<HW_I2C>(I2C_ONE));
  delay(100);
  ssd1306_dduino_display->init();
  delay(100);
  ssd1306_dduino_display->clear();
  delay(100);
#else
  // Other branches for different displays (unused in this configuration)
#endif
}

void Display::updateDisplay(String face) { 
  Display::updateDisplay(face, ""); 
}

void Display::updateDisplay(String face, String text) {
#ifdef USE_SSD1306WIRE
  if (ssd1306_dduino_display != nullptr) {
    ssd1306_dduino_display->clear();
    delay(5);
    ssd1306_dduino_display->drawString(0, 0, face);
    delay(5);
    ssd1306_dduino_display->drawString(0, 20, text);
    delay(5);
    ssd1306_dduino_display->display();
    delay(5);
  }
#else
  // Other display update branches (unused in this configuration)
#endif
}

#ifndef USE_SSD1306WIRE
// This function is only needed if you plan to use U8G2-based displays.
void Display::printU8G2Data(int x, int y, const char *data) {
  // Original U8G2-based implementation goes here.
}
#endif
