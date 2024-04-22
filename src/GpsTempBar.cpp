#include <Arduino.h>
#include "GpsTempBar.h"
#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN);

void setupGPS() {
    ss.begin(GPSBaud);
}
void getGPSData(String &message) {
    while (ss.available() > 0) {
      
        if (gps.encode(ss.read())) {
            if (gps.location.isValid()) {
                // Construct the message to send via LoRa
                message += "Lat: " + String(gps.location.lat(), 6);
                message += ", Lng: " + String(gps.location.lng(), 6);
                message += ", Alt: " + String(gps.altitude.meters(), 2);
                message += ", Sat: " + String(gps.satellites.value());
                message += ", Date: ";
                message += String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
                message += ", Time: ";
                message += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
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
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

    