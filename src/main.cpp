#include <Arduino.h>
#include "config.h"
#include "Comms.h"
#include "GpsTempBar.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"
#include <Wire.h>


void setupLoRa();

void setup(){
    Serial.begin(115200);        // Serial to computer
    setupGPS();
    setupLoRa();
    setupBME680();
}

void loop()
{ 
  getGPSData(message);
  getBME680Data(message);
  sendMessage();
}


void setup1()
{

}

void loop1()
{

}