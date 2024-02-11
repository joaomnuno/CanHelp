#ifndef CONFIG_H
#define CONFIG_H

// Data Handling
#define sendDelay 5
#define SCK_SPI_PIN 10
#define TX_SPI_PIN 11
#define RX_SPI_PIN 12
#define CS_SPI_PIN 13
#define RADIO_TX_UART1_PIN 8
#define RADIO_RX_UART1_PIN 9

// Sensor Handling
#define seaLevelPressure_hPa 1032.65
#define INTERRUPT_PIN 5
#define sensorDebug true
#define GPS_TX_UART0_PIN 16
#define GPS_RX_UART0_PIN 17
#define SDA_I2C0_PIN 20
#define SCL_I2C0_PIN 21

// Screen Handling
#define button1_pin 18
#define button2_pin 19

// Servo Handling
#define STOP_SERVO 90
#define DELAY_VALUE 700
#define SERVO_SPEED 90
#define HEADING_OBJECTIVE 77
#define threshold 7.5
#define pinServo 6

// ^Define pulses for different directions
#define STOP_PULSE 1500
#define CLOCKWISE_PULSE 1700        // Adjust as needed for clockwise rotation
#define COUNTERCLOCKWISE_PULSE 1300 // Adjust as needed for counter-clockwise rotation

#define moveDuration 1000 // duration for which the servo should move (in milliseconds)
#define lastMoveTime 0    // time when the servo last started moving

#endif