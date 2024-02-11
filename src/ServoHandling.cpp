#include "SharedData.h"
#include "ServoHandling.h"

#include <Arduino.h>
#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

int directionToGo = 0; // Direcao para onde o cansat tem de virar.
                       //  0 Se nao for para virar e -1 ou 1 otherwise (dependendo da direcao)
int magneticDirection = HEADING_OBJECTIVE;

void ServoSetup()
{
  myservo.attach(pinServo);              // attaches the servo on GIO2 to the servo object
  myservo.writeMicroseconds(STOP_PULSE); // Initially STOP_SERVO the servo
}

void HandleInstructions()
{
  // Check if new data is ready
  if (receivedData.dataReady)
  {
    switch (receivedData.instruction)
    {
    case 1:
      myservo.writeMicroseconds(CLOCKWISE_PULSE); // Rotate clockwise
      break;
    case -1:
      myservo.writeMicroseconds(COUNTERCLOCKWISE_PULSE); // Rotate counter-clockwise
      break;
    case 0:
    default:
      myservo.writeMicroseconds(STOP_PULSE); // Stop
      break;
    }
    receivedData.dataReady = false; // Reset data flag
  }
}

void ServoAdjustDirection()
{ // Ver se as condicoes iniciais estao de ==1 ou == -1 estao bem ou teem de ser trocadas. -----------------------------
  GetDirectionToGo();
  if (directionToGo == 1)
  {
    myservo.write(STOP_SERVO + SERVO_SPEED); // spin in one direction
    delay(DELAY_VALUE);                      // Ver se este tempo está certo
    myservo.write(STOP_SERVO - SERVO_SPEED); // spin in one direction
    delay(DELAY_VALUE);                      // Ver se este tempo está certo
    myservo.write(STOP_SERVO);
  }
  else if (directionToGo == -1)
  {
    myservo.write(STOP_SERVO - SERVO_SPEED); // spin in one direction
    delay(DELAY_VALUE);                      // Ver se este tempo está certo
    myservo.write(STOP_SERVO + SERVO_SPEED); // spin in one direction
    delay(DELAY_VALUE);                      // Ver se este tempo está certo
    myservo.write(STOP_SERVO);
  }
}

int GetDirectionToGo()
{ // Verificar se o angulo e a direcao sao a mesma direcao ou n ----------------------------------
  if (servoData.dataReady)
  {
    // Copy the data
    ServoData localServoData = servoData;
    servoData.dataReady = false; // Reset the flag
    magneticDirection = localServoData.heading;
    Serial.println(directionToGo);
  }
  if (abs(magneticDirection - HEADING_OBJECTIVE) <= threshold)
  {
    directionToGo = 0;
  }
  else
  {
    if (magneticDirection >= HEADING_OBJECTIVE && magneticDirection <= (HEADING_OBJECTIVE + 180))
    {
      directionToGo = 1;
    }
    else
    {
      directionToGo = -1;
    }
    /*if (magneticDirection <= HEADING_OBJECTIVE || magneticDirection >= (HEADING_OBJECTIVE + 180)) {
      directionToGo = -1;
    }*/
  }
  return 0;
}
