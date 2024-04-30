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



#endif