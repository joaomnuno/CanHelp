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
  setupBME680();
  setupIMU();
  initSharedDataStructures();
}

void loop()
{ 
  if (state == "1" || state == "2" || state == "3" || state == "4" || state == "5"){
  getGPSData(message);
  getBME680Data(message);
  getIMUData(message);

  // CODIGO DE ESCREVER NA SD
  }

  if (state == "3"){
    // PARAGLIDER CONTROL HERE
  }

  if (state == "5"){
    // PARAGLIDER MANUAL CONTROL HERE
  }

  if (state == "4"){
    // HELP CODE HERE (ASK QUESTIONS, ETC)
  }
}


void setup1()
{
  setupLoRa();
  initSD();
}

void loop1()
{
  if (state == "0"){
    onReceive(LoRa.parsePacket());
  }
  if (state == "1" || state == "2" || state == "3" || state == "4" || state == "5"){
    onReceive(LoRa.parsePacket());
    sendMessage();
  }
  
  
  
}