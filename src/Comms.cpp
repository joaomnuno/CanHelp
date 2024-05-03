#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"

#ifndef COMMS
#define COMMS
long lastSendTime = 0;     // last send time
int messageInterval = 300; // interval between sends
#endif

void resetLoRaModule()
{
  digitalWrite(loraResetPin, LOW);
  delay(10);
  digitalWrite(loraResetPin, HIGH);
  delay(10);
  setupLoRa(); // Re-run the setup function
}

void checkCommunicationHealth()
{
  static unsigned int failedPacketCount = 0;

  if (LoRa.parsePacket() == 0)
  {
    failedPacketCount++;
  }
  else
  {
    failedPacketCount = 0; // Reset on successful packet
  }

  if (failedPacketCount >= MAX_FAILED_PACKETS)
  {
    Serial.println("Resetting LoRa Module due to continuous packet loss.");
    resetLoRaModule();
    failedPacketCount = 0;
  }
}

void sendMessage(String message)
{
  LoRa.beginPacket();
  LoRa.println(message);
  LoRa.endPacket();
  // Serial.println(String(sharedData.timestamp) + "|" + String(sharedData.pressure) + "|" + String(sharedData.temperatureAmbient) + "|" + String(sharedData.height) + "|" + state + "|" + String(sharedData.IMUAccX) + "|" + String(sharedData.IMUAccY) + "|" + sharedData.helpMessage + "|" + String(sharedData.vbat));

  // delay(300); // APAGAR ISTO DEPOIS ---------------------------------------
}

void setupLoRa()
{
  // override the default CS, reset, and IRQ pins with config settings
  SPI.setCS(loraCsPin);
  SPI.setRX(pinLoraSPI_MISO);
  SPI.setTX(pinLoraSPI_MOSI);
  SPI.setSCK(pinLoraSPI_SCK);
  SPI.begin();

  LoRa.setPins(loraCsPin, loraResetPin, loraIrqPin); // set CS, reset, IRQ pin
  LoRa.setSPI(SPI);

  if (!LoRa.begin(loraFrequency))
  { // initialize ratio at XXX MHz (set in configs)
    Serial.println("LoRa init failed. Check your connections.");
    // digitalWrite(ledPin, HIGH);
    while (true)
    {
      Serial.println("Lora innit failed."); // if filed, do nothing
    }
  }
  Serial.println("LoRa Duplex - Set spreading factor");
  LoRa.setSpreadingFactor(loraSpreadingFactor); // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(loraTxPower);                 // set TX power
  // LoRa.setOCP(1000) // set LoRa overcurrent protection
  LoRa.setSignalBandwidth(loraBandwidth); // set bandwidth
  LoRa.setSyncWord(loraSyncword);         // ranges from 0-0x34, default 0x12
  LoRa.setGain(loraGain);                 // set the gain
  LoRa.enableCrc();                       // enable CRC
  LoRa.setOCP(loraOCP);

  // Increase Preamble Length for better detection
  LoRa.setPreambleLength(12); // Increase if needed

  Serial.println("LoRa init succeeded.");
}

void onReceive(int packetSize)
{
  if (packetSize == 0)
    return; // if there's no packet, return

  // read packet header bytes:
  String incoming = "";
  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }
  incoming.trim();
  Serial.println(incoming);

  if (incoming == "open")
  {
    Serial.println("Sent to Xiao!");
    Serial2.println("open");
  }
}

void loopLoRa()
{
  // checkCommunicationHealth();
  if (millis() - lastSendTime > messageInterval)
  {
    String message = "";
    message += String(millis()) + "|" + String(sharedData.pressure) + "|" + String(sharedData.temperatureAmbient) + "|" + String(sharedData.height) + "|" + state + "|" + String(sharedData.IMUAccX) + "|" + String(sharedData.IMUAccY) + "|" + sharedData.helpMessage + "|" + String(sharedData.vbat);
    sendMessage(message);
    Serial.println("Sending " + message);
    lastSendTime = millis(); // timestamp the message
  }
  // delay(1000);
  onReceive(LoRa.parsePacket());
}