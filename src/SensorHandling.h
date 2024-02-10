#ifndef SENSORHANDLING_H
#define SENSORHANDLING_H

#include "Config.h"
#include <Arduino.h>

int SensorSetup();
void HandleSensors();
void displaySensorStatus();
void displayCalStatus();
void displaySensorDetails();
void writeBNO055Register(byte reg, byte value);

#endif