#include <Arduino.h>
#include "config.h"
#include "Comms.h"
#include "GpsTempBar.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>


void setupLoRa();

void setup(){
    Serial.begin(115200);        // Serial to computer
    setupGPS();
    setupLoRa();
}

void loop()
{ 
  sendMessage();
}

// This custom version of delay() ensures that the gps object
// is being "fed".

void setup1()
{

}

void loop1()
{

}