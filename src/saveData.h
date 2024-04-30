#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <Arduino.h>
//#include "config.h"

void readData();
void initSD();
void storeData(String fileName, const String& data);
void deleteData();
String getNextFileName();

// SD configuration (Pins)
const int SD_SCK = 2;  // SPI Clock
const int SD_MISO = 4; // Master In Slave Out (MISO)
const int SD_MOSI = 7; // Master Out Slave In (MOSI)
const int SD_CS = 5;   // Slave Select (Chip Select)

#endif