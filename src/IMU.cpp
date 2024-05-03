#include "IMU.h"
#include <Arduino.h>
#include <REG.h>
#include <wit_c_sdk.h>
#include <Wire.h>
#include "Global.h"

double posX = 0, posY = 0, posZ = 0;
double velX = 0, velY = 0, velZ = 0;
double accX = 0, accY = 0, accZ = 0;
unsigned long lastUpdateTime = 0;

int32_t i2cWrite(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
int32_t i2cRead(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);

int32_t i2cWrite(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen)
{
    Wire1.beginTransmission(ucAddr);
    Wire1.write(ucReg);
    Wire1.write(p_ucVal, uiLen);
    if (Wire1.endTransmission() == 0)
    {
        return WIT_HAL_OK; // Success
    }
    return WIT_HAL_INVAL; // Error
}

int32_t i2cRead(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen)
{
    Wire1.beginTransmission(ucAddr);
    Wire1.write(ucReg);
    if (Wire1.endTransmission(false) != 0)
    {
        return WIT_HAL_INVAL; // Transmission error
    }
    if (Wire1.requestFrom((int)ucAddr, (int)uiLen) == uiLen)
    {
        for (uint32_t i = 0; i < uiLen; i++)
        {
            p_ucVal[i] = Wire1.read();
        }
        return WIT_HAL_OK; // Success
    }
    return WIT_HAL_INVAL; // Receive error
}

void IMUDataUpdate(uint32_t regIndex, uint32_t count)
{
    // This function is called when new data is available
    // We assume AX, AY, AZ are at indices 0, 1, 2, and HX, HY, HZ are at indices 3, 4, 5
    if (regIndex <= 2)
    {                                         // Accelerometer data
        float accX = sReg[AX] / 32768.0 * 16; // Convert to actual value
        float accY = sReg[AY] / 32768.0 * 16; // Convert to actual value
    }
    if (regIndex <= 5 && regIndex >= 3)
    {                        // Magnetometer data
        float hx = sReg[HX]; // Raw magnetometer readings
        float hy = sReg[HY];
        float hz = sReg[HZ];
        magneticDirection = atan2(hy, hx) * (180 / PI); // Calculate heading
    }
}

void updatePosition()
{
    unsigned long currentTime = millis();
    double deltaTime = (currentTime - lastUpdateTime) / 1000.0; // Convert ms to seconds
    lastUpdateTime = currentTime;

    // Update velocity
    velX += accX * deltaTime;
    velY += accY * deltaTime;

    // Update position
    posX += velX * deltaTime + 0.5 * accX * deltaTime * deltaTime;
    posY += velY * deltaTime + 0.5 * accY * deltaTime * deltaTime;
}

void setupIMU()
{
// For boards that allow I2C pin configuration such as ESP32
    Wire1.setSCL(SCL_PIN);
    Wire1.setSDA(SDA_PIN);
    Wire1.begin();  // Initialize the I2C bus on specific pins

    // Register the I2C communication functions directly
    WitI2cFuncRegister(i2cWrite, i2cRead);

    // Initialize the IMU
    WitInit(WIT_PROTOCOL_I2C, IMU_I2C_ADDRESS);
}

void regUpdateCallback(uint32_t reg, uint8_t len)
{
    Serial.print("Register Updated: ");
    Serial.println(reg);
}

void getIMUData()
{

    /* WitReadReg(AX, 6); // Read accelerometer and magnetometer data
    // delay(100);        // Small delay to ensure data is ready
    updatePosition(); */
    uint8_t accData[6]; // Buffer to hold 6 bytes: 2 bytes each for X, Y, Z acceleration

    // Using the acceleration register to fetch data
    if (i2cRead(IMU_I2C_ADDRESS, WIT_ACC, accData, 6) == WIT_HAL_OK)
    {
        // Convert the bytes to 16-bit integers
        int16_t ax = (int16_t)((accData[1] << 8) | accData[0]);
        int16_t ay = (int16_t)((accData[3] << 8) | accData[2]);
        int16_t az = (int16_t)((accData[5] << 8) | accData[4]);

        // Print the results to the Serial Monitor
        Serial.print("Acceleration X: ");
        Serial.println(ax);
        Serial.print("Acceleration Y: ");
        Serial.println(ay);
        Serial.print("Acceleration Z: ");
        Serial.println(az);
    }
    else
    {
        Serial.println("Failed to read acceleration data");
    }

    // Append IMU data to message
    /*sharedData.IMUAccX = accX;
    sharedData.IMUAccY = accY;
    sharedData.IMUposX = posX;
    sharedData.IMUposY = posY;
*/
    // Serial.println("IMU Data: AccX: " + String(accX) + " AccY: " + String(accY) + " PosX: " + String(posX) + " PosY: " + String(posY));
}