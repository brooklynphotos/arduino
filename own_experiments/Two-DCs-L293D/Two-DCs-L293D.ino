/**
 * https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/
*/

const int leftForward = 2;
const int leftBackward = 3;
const int leftEN = 9;
const int rightForward = 4;
const int rightBackward = 5;
const int rightEN = 10;
const int speedChangeDelay = 20;

void setup() {
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(leftEN, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(rightEN, OUTPUT);
  // shut it off first
  turnOff();
}

void turnOff(){
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
}

void speedUp(){
  for(int i=0;i<256; i++){
    analogWrite(leftEN, i);
    analogWrite(rightEN, 255-i);
    delay(speedChangeDelay);
  }
  for(int i=0;i<256; i++){
    analogWrite(rightEN, i);
    analogWrite(leftEN, 255-i);
    delay(speedChangeDelay);
  }
  turnOff();
}

void loop(){
  // run forward
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  speedUp();
}
