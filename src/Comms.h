#ifndef COMMS_H
#define COMMS_H
#include <Arduino.h>


void setupLoRa();
void sendMessage();

extern String message;
/* Message sending configuration
byte messageCount = 0;            // count of outgoing messages
int messageInterval = 50;        // interval between sends
long lastSendMessageTime = 0;      // time of last packet send
*/

// LoRa configuration (Pins)
const int loraCsPin = 17;          // LoRa radio chip select
const int loraResetPin = 21;       // LoRa radio reset
const int loraIrqPin = 20;         // change for your board; must be a hardware interrupt pin
// LoRa configuration (Settings)
const int loraTxPower = 20;          // LoRa Power setting (0-20)
const long loraFrequency = 861E6;  // LoRa frequency in Hz
const long loraSpreadingFactor = 10; // LoRa radio spreading factor
const long loraBandwidth = 500E3; // LoRa radio bandwidth
const long loraSyncword = 0x2a; // ranges from 0-0x34, default 0x34
const long loraGain = 0; // LoRa radio auto gain setting



#endif