/*
 * Based on https://dronebotworkshop.com/i2c-arduino-arduino/
*/

// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

const int potPin = A0;

void setup() {

  // Initialize I2C communications as Master
  Wire.begin();
  
  // Setup serial monitor
  Serial.begin(9600);
  Serial.println("Master started");
}

void loop() {
  delay(50);

  // Read the pot
  int potReading = analogRead(potPin);
  int ledSignal = map(potReading, 0, 1023, 0, 255);
  Serial.println("Master sending LED reading: "+String(ledSignal));
  
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(ledSignal);
  Wire.endTransmission();
}
