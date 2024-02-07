#ifndef DATAHANDLING_H
#define DATAHANDLING_H

#define sendDelay 5
#define chipSelect 13
#include <Arduino.h>

int DataHandlingSetup();
void HandleData();
bool initializeSD();
// int writeToSD(String fileName, double compass, double pressure, double temperatureAmbient, double temperatureCPU, double altitude);
int writeSpeedToSD(String fileName, double pressure, double temperatureAmbient, double altitude);
String getNextFileName();

#endif
