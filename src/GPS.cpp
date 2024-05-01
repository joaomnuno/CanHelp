#include <Arduino.h>
#include "GPS.h"
#include <TinyGPS++.h>
#include "Global.h"



TinyGPSPlus gps;

void setupGPS() {
    Serial1.begin(GPSBaud);
}

void getGPSData(String &message) {
    while (Serial1.available() > 0) {

        if (gps.encode(Serial1.read())) {
            if (gps.location.isValid()) {
                // Construct the message to send via LoRa
                //sharedData.GPSLatitude = double(gps.location.lat());
                //sharedData.GPSLongitude = double(gps.location.lng());
                //sharedData.hour = double(gps.time.hour());
                //sharedData.minute = double(gps.time.minute());
                //sharedData.second = double(gps.time.second());
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

