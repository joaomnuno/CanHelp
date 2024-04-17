#include <Arduino.h>
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include "config.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;

SoftwareSerial ss(GPS_RX_PIN, GPS_TX_PIN); // The serial connection to the GPS device

void setupLoRa();
void setup();
void loop();
void setup1();
void loop1();
long controlNumber = 0;

void setup(){
    Serial.begin(115200);        // Serial to computer
    ss.begin(GPSBaud);
    setupLoRa();
}

void loop()
{
    while (ss.available() > 0) {
        if (gps.encode(ss.read())) {
            if (gps.location.isValid()) {
                // Construct the message to send via LoRa
                String message = "Lat: " + String(gps.location.lat(), 6);
                message += ", Lng: " + String(gps.location.lng(), 6);
                message += ", Alt: " + String(gps.altitude.meters(), 2);
                message += ", Sat: " + String(gps.satellites.value());
                message += ", Control: " + String(controlNumber++);

                // Send the message via LoRa
                LoRa.beginPacket();
                LoRa.print(message);
                LoRa.endPacket();

                Serial.println("Sent: " + message);  // Debugging output
            }
        }
    }

    smartDelay(200);

    if (millis() > 5000 && gps.charsProcessed() < 10)
        Serial.println(F("No GPS data received: check wiring"));
}

void setupLoRa() {
  // override the default CS, reset, and IRQ pins with config settings
  LoRa.setPins(loraCsPin, loraResetPin, loraIrqPin); // set CS, reset, IRQ pin

  if (!LoRa.begin(loraFrequency)) { // initialize ratio at XXX MHz (set in configs)
    Serial.println("LoRa init failed. Check your connections.");
    //digitalWrite(ledPin, HIGH);
    while (true); // if failed, do nothing
  }
  Serial.println("LoRa Duplex - Set spreading factor");
  LoRa.setSpreadingFactor(loraSpreadingFactor); // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(loraTxPower); // set TX power
  //LoRa.setOCP(1000) // set LoRa overcurrent protection
  LoRa.setSignalBandwidth(loraBandwidth); // set bandwidth
  LoRa.setSyncWord(loraSyncword); // ranges from 0-0x34, default 0x12
  LoRa.setGain(loraGain); // set the gain
  LoRa.enableCrc(); // enable CRC

  Serial.println("LoRa init succeeded.");
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}

void setup1()
{

}

void loop1()
{

}