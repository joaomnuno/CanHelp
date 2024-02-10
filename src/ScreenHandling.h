#ifndef SCREENHANDLING_H
#define SCREENHANDLING_H

#include <Arduino.h>
#include "Config.h"

void ISR_button(void);
void ScreenSetup(void);
void HandleScreen();
#endif