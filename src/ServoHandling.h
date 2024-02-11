#ifndef SERVOHANDLING_H
#define SERVOHANDLING_H

#include "Config.h"

void ServoSetup();
void ServoTest();
void ServoTestSimple();
int GetDirectionToGo();
void ServoAdjustDirection();
void HandleInstructions();
#endif
