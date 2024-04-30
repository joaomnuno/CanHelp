#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"
#include <Wire.h>
#include "IMU.h"
#include "SaveData.h"
#include "ScreenHelp.h"

void setupLoRa();

void setup(){
  Serial.begin(115200);        // Serial to computer
  setupIMU();
  setupDisplay();
  initSharedDataStructures();
}

void loop()
{ 

  getIMUData();
  if (state == "3"){
    // PARAGLIDER CONTROL HERE
  }

  if (state == "5")
  {
    // PARAGLIDER MANUAL CONTROL HERE
  }

  if (state == "4")
  {
    checkButtonPresses();
  }
}

void setup1()
{
  setupLoRa();
  initSD();
}

void loop1()
{
  if (state == "0")
  {
    onReceive(LoRa.parsePacket());
  }
  if (state == "1" || state == "2" || state == "3" || state == "4" || state == "5")
  {
    onReceive(LoRa.parsePacket());
    sendMessage();
  }
}