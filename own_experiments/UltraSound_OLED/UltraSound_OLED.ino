
/**
 * Based on: https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/#1
*/

#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int baud = 9600;

// OLED
const int screenWidth = 128;
const int screenHeight = 64;
const int mosi = 9;
const int clk = 10;
const int dc = 11;
const int cs = 12;
const int reset = 13;
Adafruit_SSD1306 display(screenWidth, screenHeight, mosi, clk, dc, reset, cs);

// HC-SR04 pins
const int triggerPin = 6;
const int echoPin = 7;
const int maxDistance = 400;
const int minDistance = 2;

NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  Serial.begin(baud);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  showStarting();
}

void showStarting(){
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(1, 1);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.println("Starting distance measuring....");
  display.display();
  delay(1000);

}

void showDistance(float distance){
  display.clearDisplay();

  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(1, 1);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.println(distance);
  display.display();
  delay(1);
}

void loop() {
  float duration = sonar.ping();
  float distance = (duration / 2) * 0.0343;
  showDistance(distance);
  Serial.print("Distance = ");
  if(distance >=maxDistance || distance <= minDistance){
    Serial.println("Out of Range");
  }else{
    Serial.println(String(distance)+" cm");
  }
  delay(500);
}
