#include <Arduino.h>
#include <LoRa.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <U8g2lib.h>

File dataFile; // Global declaration of File object

void initScreen();
void setupLoRa();
void initSD();
void listFiles();

// I2C Configuration
const int pinI2C1_SDA = 10;
const int pinI2C1_SCL = 11;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, pinI2C1_SCL, pinI2C1_SDA);

// SPI configuration
const int pinLoraSPI_SCK = 18;  // SPI Clock
const int pinLoraSPI_MISO = 16; // Master In Slave Out (MISO)
const int pinLoraSPI_MOSI = 19; // Master Out Slave In (MOSI)
const int pinLoraSPI_SS = 17;   // Slave Select (Chip Select)

// SD card configuration
const int SD_SCK = 2;  // SPI Clock
const int SD_MISO = 4; // Master In Slave Out (MISO)
const int SD_MOSI = 7; // Master Out Slave In (MOSI)
const int SD_CS = 5;   // Slave Select (Chip Select)

// LoRa configuration (pins)
const int loraResetPin = 28; // LoRa radio reset
const int loraIrqPin = 26;   // change for your board; must be a hardware interrupt pin

// LoRa configuration (Settings)
const int loraTxPower = 20;         // LoRa Power setting (0-20)
const long loraFrequency = 868E6;   // LoRa frequency in Hz
const long loraSpreadingFactor = 7; // LoRa radio spreading factor
const long loraBandwidth = 125E3;   // LoRa radio bandwidth
const long loraSyncword = 0x2a;     // ranges from 0-0x34, default 0x34
const long loraGain = 0;            // LoRa radio auto gain setting
const long CodingRate4 = 5;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // setupLoRa();
  // initSD();
  // listFiles();
  initScreen();
}

void loop()
{
  /* // The loop can be used to read or send data if LoRa.begin() was successful
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // Received a packet
    Serial.print("Received packet '");

    // Read packet
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }

    // Print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  } */
}

void setupLoRa()
{
  SPI.setRX(pinLoraSPI_MISO);
  SPI.setTX(pinLoraSPI_MOSI);
  SPI.setSCK(pinLoraSPI_SCK);
  SPI.setCS(pinLoraSPI_SS);
  SPI.begin(); // Initialize SPI interface
  LoRa.setSPI(SPI);
  LoRa.setPins(pinLoraSPI_SS, loraResetPin, loraIrqPin); // Set CS, reset, IRQ pin

  if (!LoRa.begin(loraFrequency))
  {
    Serial.println("LoRa init failed. Check your connections.");
    while (true)
      ; // Halt execution if initialization fails
  }

  Serial.println("LoRa Duplex - Set spreading factor");
  LoRa.setSpreadingFactor(loraSpreadingFactor); // ranges from 6-12, default 7 see API docs
  LoRa.setTxPower(loraTxPower);                 // set TX power
  LoRa.setSignalBandwidth(loraBandwidth);       // set bandwidth
  LoRa.setSyncWord(loraSyncword);               // Sync word configuration
  LoRa.setGain(loraGain);                       // Gain setting
  LoRa.enableCrc();                             // Enable CRC for packet integrity
  LoRa.setOCP(240);                             // Over Current Protection setting

  // Increase Preamble Length for better detection
  LoRa.setPreambleLength(12); // Increase if needed

  Serial.println("LoRa init succeeded.");
}

void initSD()
{
  // Initialize SD card with custom SPI settings
  SPI.setRX(SD_MISO);
  SPI.setTX(SD_MOSI);
  SPI.setSCK(SD_SCK);

  if (!SD.begin(SD_CS, SPI))
  {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");
}

void storeData(const String &fileName, const String &data)
{
  dataFile = SD.open(fileName, FILE_WRITE); // Open the file for writing
  if (dataFile)
  {
    dataFile.println(data);
    dataFile.close();
    // Uncomment the following line for debugging
    // Serial.println("Data stored on SD Card.");
  }
  else
  {
    Serial.println("Error opening " + fileName);
  }
}

void listFiles()
{
  File root = SD.open("/"); // Open root directory
  if (root)
  {
    Serial.println("Listing files:");
    while (true)
    {
      File entry = root.openNextFile();
      if (!entry)
      {
        break; // No more files
      }
      Serial.print(entry.name());
      if (entry.isDirectory())
      {
        Serial.println("/");
      }
      else
      {
        Serial.print("\t\t");
        Serial.println(entry.size(), DEC); // Print the file size
      }
      entry.close();
    }
    root.close();
  }
  else
  {
    Serial.println("Failed to open directory.");
  }
}

void initScreen()
{
  if (!u8g2.begin())
  {
    Serial.println("U8g2 initialization failed");
    while (1)
      ;
  }
  else
  {
    Serial.println("U8g2 initialized!");
  }
}