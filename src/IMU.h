#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#define IMU_I2C_ADDRESS 0x50 // Example address, replace with the actual address

// Function prototypes for I2C read and write

void setupIMU();
void getIMUData();
void IMUDataUpdate(uint32_t regIndex, uint32_t count);
void updatePosition();

#endif // IMU_H