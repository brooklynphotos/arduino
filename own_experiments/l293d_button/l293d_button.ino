/**
 * https://toptechboy.com/arduino-tutorial-38-using-a-tilt-switch-cut-off-with-a-dc-motor/
 * Use DC motor with button
 */
#define UP 1
#define DOWN 0

const int baud = 9600;
const int stepsPR = 2048;
int motSpeed = 2; // in RPM from 2 to 19
const int buttonPin = 2;
const int leftDriverPin = 9;
const int leftDirPin1 = 8;
const int leftDirPin2 = 7;
const int rightDriverPin = 6;
const int rightDirPin1 = 4;
const int rightDirPin2 = 12;

const int delayTime = 200;
int motDir = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(leftDriverPin, OUTPUT);
  pinMode(leftDirPin1, OUTPUT);
  pinMode(leftDirPin2, OUTPUT);
  pinMode(rightDriverPin, OUTPUT);
  pinMode(rightDirPin1, OUTPUT);
  pinMode(rightDirPin2, OUTPUT);
  Serial.begin(baud);
}

void loop() {
  int buttonVal = digitalRead(buttonPin);
  Serial.println("Button: "+String(buttonVal));
  runMotor(buttonVal==DOWN);
  delay(delayTime);
}

void runMotor(boolean on) {
  digitalWrite(leftDirPin1, HIGH);
  digitalWrite(leftDirPin2, on ? LOW : HIGH);
  analogWrite(leftDriverPin, 255);

  digitalWrite(rightDirPin1, HIGH);
  digitalWrite(rightDirPin2, LOW);
//  digitalWrite(rightDirPin2, on ? LOW : HIGH);
  analogWrite(rightDriverPin, 255);

}
