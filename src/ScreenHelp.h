#ifndef SCREENHELP_H
#define SCREENHELP_H

#define BITMAP_HEIGHT 64
#define BITMAP_WIDTH 128

#include <Arduino.h>

// Wire 2 pins
const int pinButton1 = 6;
const int pinButton2 = 3;
const int ScreeniicData = 10;
const int ScreeniicClock = 11;

// Declare functions
void setupDisplay();
void checkButtonPresses();
void changeBitmap();

// Declare the display object for an SSH1106 display using the constructor from U8g2 library
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

#endif