#include <Arduino.h>
#include "GpsTempBar.h"
#include <Arduino.h>
#include <TinyGPS++.h>
#include "Global.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>



TinyGPSPlus gps;
Adafruit_BME680 bme; // Initialize the BME680 sensor instance
double groundPressure;

void setupGPS() {
    Serial1.begin(GPSBaud);
}

void setupBME680() {
    if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
    } else {
        // Set up oversampling and filter initialization
        bme.setTemperatureOversampling(BME680_OS_2X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_2X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        // bme.setGasHeater(320, 150); // 320*C for 150 ms
        delay(200);
        bme.performReading();
        groundPressure = bme.pressure;

    }
}

void getBME680Data(String &message) {
    if (!bme.performReading()) {
        message += " Failed to perform reading from BME680.";
        return;
    }
    sharedData.temperatureAmbient = double(bme.temperature);
    sharedData.pressure = double(bme.pressure / 100.0);
    sharedData.altitude = ((groundPressure - sharedData.pressure) / 12,7) * 100;
}

void getGPSData(String &message) {
    while (Serial1.available() > 0) {
      
        if (gps.encode(Serial1.read())) {
            if (gps.location.isValid()) {
                // Construct the message to send via LoRa
                sharedData.GPSLatitude = double(gps.location.lat());
                sharedData.GPSLongitude = double(gps.location.lng());
                sharedData.hour = double(gps.time.hour());
                sharedData.minute = double(gps.time.minute());
                sharedData.second = double(gps.time.second());
            }
        }
    }

    smartDelay(200);
    Serial.println("Fiding Satellite...");
    
    
    if (millis() > 5000 && gps.charsProcessed() < 10)
        Serial.println(F("No GPS data received: check wiring"));
}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

    