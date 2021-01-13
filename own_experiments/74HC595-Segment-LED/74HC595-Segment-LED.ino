/*
  74HC595 Shift Register with 7-segment LED display
  74hc595-7segdisplay.ino
  Count in hex from 0-F and display on 7-segment Common Cathode LED display

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Define Connections to 74HC595

// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;

// Patterns for characters 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F, 8.
int datArray[17] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110, B11101110, B00111110, B10011100, B01111010, B10011110, B10001110, B11111111};

void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  // Count from 0 to 15
  for (int num = 0; num < 17; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    Serial.println("Writing "+String(num));

    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, datArray[num]);

    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);

    delay(1000);
  }
}
