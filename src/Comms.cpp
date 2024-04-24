#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"

short controlNumber = 0;


void sendMessage()
{
  message = String(controlNumber++);
  LoRa.beginPacket();
  delay(300); // APAGAR ISTO DEPOIS ---------------------------------------
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println("Sent: " + message); // Debugging output
}

void setupLoRa()
{
  // override the default CS, reset, and IRQ pins with config settings
  LoRa.setPins(loraCsPin, loraResetPin, loraIrqPin); // set CS, reset, IRQ pin

  if (!LoRa.begin(loraFrequency))
  { // initialize ratio at XXX MHz (set in configs)
    Serial.println("LoRa init failed. Check your connections.");
    // digitalWrite(ledPin, HIGH);
    while (true)
      ; // if failed, do nothing
  }
  Serial.println("LoRa Duplex - Set spreading factor");
  LoRa.setSpreadingFactor(loraSpreadingFactor); // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(loraTxPower);                 // set TX power
  // LoRa.setOCP(1000) // set LoRa overcurrent protection
  LoRa.setSignalBandwidth(loraBandwidth); // set bandwidth
  LoRa.setSyncWord(loraSyncword);         // ranges from 0-0x34, default 0x12
  LoRa.setGain(loraGain);                 // set the gain
  LoRa.enableCrc();                       // enable CRC
  LoRa.setOCP(240);

  // Increase Preamble Length for better detection
  LoRa.setPreambleLength(12); // Increase if needed

  Serial.println("LoRa init succeeded.");
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;  // if there's no packet, return

  // read packet header bytes:
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  // Print for debugging
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();

  // Store the data in shared structure
  mutex_enter_blocking(&loraData.lock);
  strncpy(loraData.message, incoming.c_str(), sizeof(loraData.message));
  loraData.message[sizeof(loraData.message) - 1] = '\0';  // Ensure null termination
  loraData.rssi = LoRa.packetRssi();
  loraData.snr = LoRa.packetSnr();
  loraData.dataReady = true;
  mutex_exit(&loraData.lock);
}
