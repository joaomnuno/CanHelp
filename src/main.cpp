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

void setup()
{
  Serial.begin(115200); // Serial to computer
  // setupIMU();
  setupDisplay();
  // initSharedDataStructures();
  setupSerialComs();
  setupLoRa();
}

void loop()
{
  // getIMUData();
  if (state == "3")
  {
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
  checkButtonPresses();
  loopSerialComs();
  loopLoRa();
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