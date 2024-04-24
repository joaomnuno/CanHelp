#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

extern String message;
extern String state;
extern float magneticDirection; // Global variable to store magnetic direction


struct LoRaData {
    char message[256];
    int rssi;
    float snr;
    mutex_t lock;
    volatile bool dataReady;
};

extern LoRaData loraData;

void initSharedDataStructures();

struct SharedData {
  double compass, pressure, temperatureAmbient, temperatureCPU, altitude;
  volatile bool dataReady;  // Flag to indicate new data is ready
};

struct ServoData{
  double heading;
  volatile bool dataReady; // Flag to indicate new data is ready
};

struct ReceivedData {
  int instruction;
  volatile bool dataReady; // Flag to indicate new data is ready
};

extern SharedData sharedData;  // Declaration of the shared data object
extern ServoData servoData;  // Declaration of the shared data object
extern ReceivedData receivedData;  // Declaration of the received data object

#endif
