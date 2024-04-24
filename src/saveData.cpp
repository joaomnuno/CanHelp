#include <SD.h>
#include <SPI.h>
#include "SaveData.h"
#include "Global.h"
// #include "config.h"

File dataFile;

void initSD() {
    // Initialize SD card with custom SPI settings
    SPI1.setRX(SD_MISO);
    SPI1.setTX(SD_MOSI);
    SPI1.setSCK(SD_SCK);

    if (!SD.begin(SD_CS, SPI1)) {
        Serial.println("SD Card initialization failed!");
        return;
    }
    Serial.println("SD Card initialized.");
}

void storeData(String fileName, const String& data) {
    dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
        dataFile.println(data);
        dataFile.close();
        //Serial.println("Data stored on SD Card.");
    }
    else {
        Serial.println("Error opening data.txt");
    }
}

void readData() {
    dataFile = SD.open("data1.csv", FILE_READ); // Open the file for reading
    if (dataFile) {
        Serial.println("Reading data from SD Card:");
        while (dataFile.available()) {
            Serial.write(dataFile.read()); // Read the file until there's nothing else in it
        }
        dataFile.close(); // Close the file
    }
    else {
        Serial.println("Failed to open data.txt for reading.");
    }
}

void deleteData() {
    if (SD.exists("data1.csv")) {
        SD.remove("data.csv");
        Serial.println("Data file deleted successfully.");
    }
    else {
        Serial.println("Data file does not exist.");
    }
}

String getNextFileName()
{
    int fileNumber = 1000; // Start with file number 1
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