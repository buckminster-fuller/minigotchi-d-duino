/**
 * display.h: header file for display.cpp
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

#ifdef USE_SSD1306WIRE
  // For d-duino board only
  #include "SSD1306Wire.h"
#else
  // For other boards (not used in this configuration)
  #include <Adafruit_GFX.h>
  #include <Adafruit_SH110X.h>
  #include <Adafruit_SSD1305.h>
  #include <Adafruit_SSD1306.h>
  #include <SPI.h>
  #include <U8g2lib.h>
  #include <Wire.h>
#endif

#define SSD1306_SCREEN_WIDTH 128
#define SSD1306_SCREEN_HEIGHT 64

// (Other definitions could remain if needed)

class Display {
public:
  ~Display();
  static void startScreen();
  static void updateDisplay(String face);
  static void updateDisplay(String face, String text);

#ifndef USE_SSD1306WIRE
  // Only needed if using the U8G2 branch for text-wrapping
  static void printU8G2Data(int x, int y, const char *data);
#endif
};

#endif // DISPLAY_H
