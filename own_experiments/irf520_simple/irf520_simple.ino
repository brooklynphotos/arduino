/**
 * Testing out laser
 * https://arduinomodules.info/ky-008-laser-transmitter-module/
 */

const int irfPin = 6;
int delayTime = 100;
int motorSpeed = 255;

void setup() {
  Serial.begin(9600);
  pinMode(irfPin, OUTPUT);
}

void loop() {
  analogWrite(irfPin, motorSpeed);
  motorSpeed = (motorSpeed + 1) % 256;
  Serial.println(motorSpeed);
  delay(delayTime);
}
