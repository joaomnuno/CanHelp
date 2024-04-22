#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>

short controlNumber = 0;

void sendMessage() {
  message = String(controlNumber++);
  LoRa.beginPacket();
  delay(300);  // APAGAR ISTO DEPOIS ---------------------------------------
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println("Sent: " + message);  // Debugging output
}

void setupLoRa() {
  // override the default CS, reset, and IRQ pins with config settings
  LoRa.setPins(loraCsPin, loraResetPin, loraIrqPin); // set CS, reset, IRQ pin

  if (!LoRa.begin(loraFrequency)) { // initialize ratio at XXX MHz (set in configs)
    Serial.println("LoRa init failed. Check your connections.");
    //digitalWrite(ledPin, HIGH);
    while (true); // if failed, do nothing
  }
  Serial.println("LoRa Duplex - Set spreading factor");
  LoRa.setSpreadingFactor(loraSpreadingFactor); // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(loraTxPower); // set TX power
  //LoRa.setOCP(1000) // set LoRa overcurrent protection
  LoRa.setSignalBandwidth(loraBandwidth); // set bandwidth
  LoRa.setSyncWord(loraSyncword); // ranges from 0-0x34, default 0x12
  LoRa.setGain(loraGain); // set the gain
  LoRa.enableCrc(); // enable CRC

  Serial.println("LoRa init succeeded.");
}