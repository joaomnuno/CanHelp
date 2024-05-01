#ifndef GPS_H
#define GPS_H

#include <Arduino.h>



static void smartDelay(unsigned long ms);
void getGPSData(String &message);
void setupGPS();


// GPS configuration
const long GPS_RX_PIN = 1;
const long GPS_TX_PIN = 0;
static const uint32_t GPSBaud = 9600; //GPS Baud Rate


#endif