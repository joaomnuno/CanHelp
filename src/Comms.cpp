#include <Arduino.h>
#include "Comms.h"
#include <SPI.h>
#include <LoRa.h>
#include "Global.h"


void sendMessage()
{
  LoRa.beginPacket();
 // mutex_enter_blocking(&loraData.lock);
  LoRa.print(String(sharedData.pressure) + "|" + String(sharedData.temperatureAmbient) + "|" + String(sharedData.height) + "|" + state + "|" + String(sharedData.IMUAccX) + "|" + String(sharedData.IMUAccY) + "|" + (sharedData.helpMessage) + "|" + String(sharedData.vbat));
// mutex_exit(&loraData.lock);
  LoRa.endPacket();
  delay(100); // APAGAR ISTO DEPOIS ---------------------------------------
}

void setupLoRa()
{
  // override the default CS, reset, and IRQ pins with config settings

  LoRa.setPins(17, 21, 20); // set CS, reset, IRQ pin

  if (!LoRa.begin(loraFrequency))
  { // initialize ratio at XXX MHz (set in configs)
    Serial.println("LoRa init failed. Check your connections.");
    // digitalWrite(ledPin, HIGH);
    while (true){
     Serial.println("Lora innit failed.");  // if filed, do nothing
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

  // Assume que a mensagem recebida vem na forma de STATE|flightStage|STEER , por exemplo - > 1|3|112

  if (packetSize == 0)
    return; // if there's no packet, return

  // read packet header bytes:
  String incoming = "";
  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }


  /*if (state != "-1")
  {
    state = incoming.substring(0, 1);
  }

  if (flightStage != "-1")
  {
    flightStage = incoming.substring(2, 3);
  }
*/
  steer = incoming.substring(2, 3).toInt();

  // Print for debugging
  Serial.println(LoRa.packetRssi());
  Serial.println(LoRa.packetSnr());

  Serial.println("Message: " + incoming);
  Serial.println();

  /* Store the data in shared structure
  mutex_enter_blocking(&loraData.lock);
  strncpy(loraData.message, incoming.c_str(), sizeof(loraData.message));
  loraData.message[sizeof(loraData.message) - 1] = '\0'; // Ensure null termination
  loraData.dataReady = true;
  mutex_exit(&loraData.lock);*/
}
  