#include "Global.h"
#include "pico/sync.h"

SharedData sharedData;
LoRaData loraData;


int flightCheck = 0; 
String message = "";
String state = "2";
float magneticDirection;
int steer = 0;
String flightStage = "0";

void initSharedDataStructures()
{

}

void updateState()
{
    if (sharedData.height > 300  && flightStage == "0"){
    flightCheck++;
    }
    if (sharedData.height < 300 && flightStage == "1"){
    flightCheck++;
    }
    if (state == "2" && flightCheck >= 10 && flightStage == 0)
    {
        flightCheck = 0;
        flightStage = "1";
    }
    else if (flightStage = "1" && flightCheck >= 10)
    {
        flightStage = "2";
        flightCheck++;
    }
    else if (flightStage = "2")
    {
        Serial2.println("open");
        flightStage = "3";
        state = "3";
    };
}

/*
Stages

-1 - Doesn't change
0 - Liftoff
1 - Parachute fall
2 - Paraglider activation
3 - Paraglider fall and foward

/

/
States

-1 - doesn't change
0 - not ready
1 - ready
2 - armed
3 - flight
4 - Help
5 - Manual control

*/