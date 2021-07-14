/**
 * Testing out laser
 * https://arduinomodules.info/ky-008-laser-transmitter-module/
 */

const int laserPin = 6;
int delayTime = 50;

void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
}

void loop() {
  digitalWrite(laserPin, HIGH);
  delay(delayTime * 10);
  digitalWrite(laserPin, LOW);
  delay(delayTime);
}
