#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"
#include <Wire.h>
#include "IMU.h"
#include "SaveData.h"
#include "ScreenHelp.h"
#include "SerialComs.h"

String fileName;

void setup()
{
  sharedData.helpMessage = "0";
  Serial.begin(115200); // Serial to computer
  //setupIMU();
  setupDisplay();
  // initSharedDataStructures();
  fileName = getNextFileName();
  setupSerialComs();
  setupLoRa();
  initSD();
}

void loop()
{
  //getIMUData();
  checkButtonPresses();
  loopSerialComs();
  loopLoRa();
  loopSD(fileName);
  updateState();
}

void setup1()
{
  // initSD();
}

void loop1()
{
  /* if (state == "0")
  {
    onReceive(LoRa.parsePacket());
  }
  if (state == "1" || state == "2" || state == "3" || state == "4" || state == "5")
  {
    onReceive(LoRa.parsePacket());
    sendMessage();
  } */
}