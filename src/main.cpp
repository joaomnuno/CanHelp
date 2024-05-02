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
  setupLoRa();
   //setupIMU();
  //setupDisplay();
  //initSharedDataStructures();
  //setupSerialComs();
  
}

void loop()
{
  //getIMUData();
  //sendMessage();
  onReceive(LoRa.parsePacket());
  //Serial.println("sent data");
  /*
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
    //checkButtonPresses();
  }
  
  //loopSerialComs(); */
}
/*
void setup1()
{

  //initSD();
  sharedData.pressure = 9999;
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
    //sendMessage();
  }
  Serial.println("yay");
  //sendMessage();
  Serial.println("sent data");
} */