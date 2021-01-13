/*
 * Based on https://dronebotworkshop.com/i2c-arduino-arduino/
*/

// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

const int ledPin = 6;

void setup() {

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);
  
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  
  // Setup Serial Monitor 
  Serial.begin(9600);
  Serial.println("I2C Slave Started");
}

void receiveEvent() {
  // Read while data received
  if (0 < Wire.available()) {
    int x = Wire.read();
    analogWrite(ledPin, x);
    Serial.println("Got "+String(x));
  }else{
    Serial.println("Got nothing");
  }
}

void loop() {

  // Time delay in loop
  delay(50);
}
