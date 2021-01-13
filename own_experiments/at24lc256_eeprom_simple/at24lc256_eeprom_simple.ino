/*
 * Simple testing of AT24LC256
 * User writes in chars that are recorded in the addresses of the EEProm
 * User can type P to play back everything
 * Based on: https://dronebotworkshop.com/eeprom-arduino/
 * 
*/

// Include the I2C Wire Library
#include "Wire.h"

// EEPROM I2C Address
#define EEPROM_I2C_ADDRESS 0x50

// special inputs
#define NEWLINE 10
#define PLAYBACK 80
#define MAX_ADDRESS 255

// Byte to hold data read from EEPROM
int readVal = 0;

// Integer to hold number of addresses to fill
int maxaddress = 1500;

int currentAddress = 0;

// Function to write to EEPROOM
void writeEEPROM(int address, byte val, int i2c_address)
{
  Serial.println("Writing to address ["+String(address)+"] value="+String(val)+" via i2c address="+String(i2c_address));
  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);

  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB

  // Send data to be stored
  Wire.write(val);

  // End the transmission
  Wire.endTransmission();

  // Add 5ms delay for EEPROM
  delay(5);
}

// Function to read from EEPROM
byte readEEPROM(int address, int i2c_address)
{
  // Define byte for received data
  byte rcvData = 0xFF;

  // Begin transmission to I2C EEPROM
  Wire.beginTransmission(i2c_address);

  // Send memory address as two 8-bit bytes
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB

  // End the transmission
  Wire.endTransmission();

  // Request one byte of data at current memory address
  Wire.requestFrom(i2c_address, 1);

  // Read the data and assign to variable
  rcvData =  Wire.read();

  // Return the data as function output
  return rcvData;
}


void setup()
{
  // Connect to I2C bus as master
  Wire.begin();

  // Setup Serial Monitor
  Serial.begin(9600);

  // Print to Serial Monitor
  Serial.println("Start Recording...");
}

void playBack(){
  Serial.println("Playing back...");
  int finalAddress = readEEPROM(0, EEPROM_I2C_ADDRESS);
  Serial.println("Reading up to address="+String(finalAddress));
  for(int a=1; a<=finalAddress;a++){
    byte v = readEEPROM(a, EEPROM_I2C_ADDRESS);
    Serial.println(v, DEC);
  }
}

void loop()
{
  if(Serial.available()>0){
    int bytes = Serial.read();
    switch(bytes){
      case NEWLINE:
        Serial.println("Got Newline");
        break;
      case PLAYBACK:
        Serial.println("Playing back");
        playBack();
        break;
      default:
        currentAddress += 1;
        // note down in address  0 the max address written to
        writeEEPROM(0, currentAddress,EEPROM_I2C_ADDRESS);
        // write the input value
        writeEEPROM(currentAddress, bytes, EEPROM_I2C_ADDRESS);
        Serial.println("Got: "+String(bytes, DEC));
    }
  }
}
