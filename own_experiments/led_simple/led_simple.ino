/**
 * Testing out dht22
 * https://dronebotworkshop.com/arduino-temperature/
 */

const int ledPin = 5;
int delayTime = 100;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}
