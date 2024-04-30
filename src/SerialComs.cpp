#include "SerialComs.h"
#include "Global.h"

// ReceivedData receivedData; // Declaration of the received data object
// SharedData sharedData;     // Declaration of the shared data object

double pressure;
double temperature;
double height;
double vbat;

void setupSerialComs()
{
    // Start Serial comms with raspberry pi pico
    Serial2.setRX(UART_RX_PIN);
    Serial2.setTX(UART_TX_PIN);
    Serial2.begin(UART_BAUD_RATE);
}

void loopSerialComs()
{
    // available message:
    while (Serial2.available() > 0)
    {
        // "control,operation\n" (if -1, then no instruction)
        String message = Serial2.readStringUntil('\n');
        parseString(message, pressure, height, temperature, vbat);
        // receivedData.gliderInstruction = gliderInstruction;
        sharedData.pressure = pressure;
        sharedData.height = height;
        sharedData.temperatureAmbient = temperature;
        sharedData.vbat = vbat;
    }
}

void parseString(const String &input, double &num1, double &num2, double &num3, double &num4)
{
    int firstCommaIndex = input.indexOf(',');
    if (firstCommaIndex == -1)
    {
        Serial.println("Error: First comma missing in string.");
        return;
    }

    int secondCommaIndex = input.indexOf(',', firstCommaIndex + 1);
    if (secondCommaIndex == -1)
    {
        Serial.println("Error: Second comma missing in string.");
        return;
    }

    int thirdCommaIndex = input.indexOf(',', secondCommaIndex + 1);
    if (thirdCommaIndex == -1)
    {
        Serial.println("Error: Third comma missing in string.");
        return;
    }

    num1 = input.substring(0, firstCommaIndex).toInt();
    num2 = input.substring(firstCommaIndex + 1, secondCommaIndex).toInt();
    num3 = input.substring(secondCommaIndex + 1, thirdCommaIndex).toInt();
    num4 = input.substring(thirdCommaIndex + 1).toInt();
}
