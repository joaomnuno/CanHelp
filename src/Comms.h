#ifndef COMMS_H
#define COMMS_H
#include <Arduino.h>

void resetLoRaModule();
void checkCommunicationHealth();
void setupLoRa();
void sendMessage();
void onReceive(int packetSize);

void loopLoRa();

/* Message sending configuration
byte messageCount = 0;            // count of outgoing messages
int messageInterval = 50;        // interval between sends
long lastSendMessageTime = 0;      // time of last packet send
*/

// LoRa configuration (Pins)
const int pinLoraSPI_MISO = 16; // Master In Slave Out (MISO)
const int pinLoraSPI_MOSI = 19; // Master Out Slave In (MOSI)
const int loraCsPin = 17;       // LoRa radio chip select
const int pinLoraSPI_SCK = 18;  // SPI Clock
const int loraResetPin = 28;    // LoRa radio reset
const int loraIrqPin = 26;      // change for your board; must be a hardware interrupt pin

// LoRa configuration (Settings)
const int loraTxPower = 20;         // LoRa Power setting (0-20)
const long loraFrequency = 868E6;   // LoRa frequency in Hz
const long loraSpreadingFactor = 7; // LoRa radio spreading factor
const long loraBandwidth = 125E3;   // LoRa radio bandwidth
const long loraSyncword = 0x2a;     // ranges from 0-0x34, default 0x34
const long loraGain = 6;            // LoRa radio auto gain setting
const long CodingRate4 = 5;
const int loraOCP = 255;
const int MAX_FAILED_PACKETS = 3;
#endif