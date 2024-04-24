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
const int SD_MISO = 0; // AKA SPI RX for SD
const int SD_MOSI = 0; // AKA SPI TX for SD
const int SD_CS = 0;   // Chip Select for SD
const int SD_SCK = 0;  // Serial Clock for SD

#endif