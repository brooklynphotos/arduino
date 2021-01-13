/**
 * For conversion to adafruit 8-pin OLED: https://circuitdigest.com/article/ssd1306-oled-display
 **/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9 // D1
#define OLED_CLK   10 // D0
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13 // RES
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
