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
#include "IMU.h"
#include "SaveData.h"

void setupLoRa();

void setup(){
    Serial.begin(115200);        // Serial to computer
    setupGPS();
    setupLoRa();
    setupBME680();
    setupIMU();
}

void loop()
{ 
  if (state == "not_ready") {
    state = loraData.message;
  };

  getGPSData(message);
  getBME680Data(message);
  getIMUData(message);
  initSharedDataStructures();
  sendMessage();
}


void setup1()
{

}

void loop1()
{

}