/**
 * https://www.youtube.com/watch?v=B6YEQj4d5WU
 * Use joystick to control LEDs
 */

#include <Servo.h>

const int baud = 9600;
const int delayTime = 500;
// joystick pins
const int joystickXPin = A0;
const int joystickYPin = A1;
const int joystickSwitchPin = 7;

void setup() {
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);
  pinMode(joystickSwitchPin, INPUT_PULLUP);
  Serial.begin(baud);
}

void loop() {
  int switchValue = digitalRead(joystickSwitchPin);
  int xValue = analogRead(joystickXPin);
  int yValue = analogRead(joystickYPin);
  Serial.println("("+String(xValue)+","+String(yValue)+","+String(switchValue)+")");
  delay(delayTime);

}
