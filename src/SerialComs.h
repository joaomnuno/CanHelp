// RASPBERRY PI PICO - SERIAL COMMS
#ifndef SERIAL_COMS_H
#define SERIAL_COMS_H

#include <Arduino.h>

const int UART_TX_PIN = 0;
const int UART_RX_PIN = 1;
const int UART_BAUD_RATE = 9600;

void setupSerialComs();
void loopSerialComs();
void parseString(const String &input, double &num1, double &num2, double &num3, double &num4);

#endif