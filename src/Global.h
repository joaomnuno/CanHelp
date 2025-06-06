#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

extern String message;
extern String state;
extern int steer;
extern float magneticDirection; // Global variable to store magnetic direction
extern bool GPSReady;
extern bool BME680Ready;
extern bool IMUReady;
extern String flightStage;

struct LoRaData
{
  char message[256];
  // int rssi;
  // float snr;
  mutex_t lock;
  volatile bool dataReady;
};

extern LoRaData loraData;

void initSharedDataStructures();

struct SharedData
{
  double timestamp, pressure, temperatureAmbient, height, state, IMUAccX, IMUAccY;
  String helpMessage;
  volatile bool dataReady; // Flag to indicate new data is ready
  double vbat;
};

struct ServoData
{
  double heading;
  volatile bool dataReady; // Flag to indicate new data is ready
  double vbat;
};

struct ReceivedData
{
  int instruction;
  volatile bool dataReady; // Flag to indicate new data is ready
};

extern SharedData sharedData;     // Declaration of the shared data object
extern ReceivedData receivedData; // Declaration of the received data object

#endif
