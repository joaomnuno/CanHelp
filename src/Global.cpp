#include "Global.h"
#include "pico/sync.h"


SharedData sharedData;
LoRaData loraData;

String message = "";
String state = "0";
float magneticDirection;
int steer = 0;
String flightStage = "0";

void initSharedDataStructures() {
    mutex_init(&loraData.lock);
}

void updateState(String newState) {
    if(state = "2" && sharedData.altitude > 400) {
        flightStage = "1";
    } else if (flightStage = "1" && sharedData.altitude < 130) {
        flightStage = "2";
    } else if (flightStage = "2") {
        // código para cortar o fio e largar o paraquedas --------
        flightStage = "3";
        state = "3";
    };
}

/*
Stages_

-1 - Doesn't change
0 - Liftoff
1 - Parachute fall
2 - Paraglider activation
3 - Paraglider fall and foward

*/



/*
States 

-1 - doesn't change
0 - not ready
1 - ready
2 - armed
3 - flight
4 - Help
5 - Manual control

*/
