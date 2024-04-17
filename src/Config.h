#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// LoRa configuration (Pins)
const int loraCsPin = 17;          // LoRa radio chip select
const int loraResetPin = 21;       // LoRa radio reset
const int loraIrqPin = 20;         // change for your board; must be a hardware interrupt pin
// LoRa configuration (Settings)
const int loraTxPower = 20;          // LoRa Power setting (0-20)
const long loraFrequency = 861E6;  // LoRa frequency in Hz
const long loraSpreadingFactor = 7; // LoRa radio spreading factor
const long loraBandwidth = 125E3; // LoRa radio bandwidth
const long loraSyncword = 0x2a; // ranges from 0-0x34, default 0x34
const long loraGain = 0; // LoRa radio auto gain setting

// LED configuration
// const int ledPin = 10;                 // LED connected to digital pin GP10
// unsigned long lastBlinkTime = 0;       // Last time the LED was turned on
// const unsigned long blinkInterval = 50; // LED on duration in milliseconds
// bool ledOn = false;

// GPS configuration
const long GPS_RX_PIN = 1;
const long GPS_TX_PIN = 0;
static const uint32_t GPSBaud = 9600;


// Message sending configuration
byte messageCount = 0;            // count of outgoing messages
int messageInterval = 50;        // interval between sends
long lastSendMessageTime = 0;      // time of last packet send


#endif