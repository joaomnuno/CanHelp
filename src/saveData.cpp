#include <SD.h>
#include <SPI.h>
#include "SaveData.h"
#include "Global.h"
// #include "config.h"

File dataFile;

void initSD()
{
    // Initialize SD card with custom SPI settings
    SPI.setRX(SD_MISO);
    SPI.setTX(SD_MOSI);
    SPI.setSCK(SD_SCK);

    if (!SD.begin(SD_CS, SPI))
    {
        Serial.println("SD Card initialization failed!");
        return;
    }
    Serial.println("SD Card initialized.");
}

void storeData(String fileName, const String &data)
{
    dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile)
    {
        dataFile.println(data);
        dataFile.close();
        // Serial.println("Data stored on SD Card.");
    }
    else
    {
        Serial.println("Error opening data.txt");
    }
}

void loopSD(String fileName)
{
    String data = "";
    data += String(sharedData.timestamp) + "|" +String(sharedData.pressure) + "|" + String(sharedData.temperatureAmbient) + "|" + String(sharedData.height) + "|" + state + "|" +  String(sharedData.IMUAccX) + "|" + String(sharedData.IMUAccY) + "|" + sharedData.helpMessage + "|" + String(sharedData.vbat);
    storeData(fileName, data);
    Serial.println("Data stored on SD Card.");
}

String getNextFileName()
{
    int fileNumber = 1; // Start with file number 1
    char fileName[20];  // Buffer to hold the file name

    while (true)
    {
        sprintf(fileName, "data%04d.csv", fileNumber); // Format with leading zeros
        if (!SD.exists(fileName))
        {
            // File does not exist, we can use this name
            break;
        }
        fileNumber++;
    }

    return fileName;
}