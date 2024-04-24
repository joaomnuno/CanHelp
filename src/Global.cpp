#include "Global.h"
#include "pico/sync.h"

LoRaData loraData;

void initSharedDataStructures() {
    mutex_init(&loraData.lock);
}

String message = "";
String state = "not_ready";
float magneticDirection;
