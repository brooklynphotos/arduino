/**
 * Testing out TB Motor Shield
 * https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor1->setSpeed(150);
  motor2->setSpeed(150);
  motor1->run(FORWARD);
  motor2->run(BACKWARD);
}

void loop() {
}
