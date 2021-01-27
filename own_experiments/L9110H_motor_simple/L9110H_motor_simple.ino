/**
 * Based on data sheet of L9110H
 * https://www.elecrow.com/download/datasheet-l9110.pdf
 * Another place to look:
 * https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 * If using microcontroller, the voltage needs to be the same as MC because there is no separate logical drive and motor drive
*/

const int IBpin = 3;
const int IApin = 4;

const int baud = 9600;
const int delayTime = 500;

const int minSpeed = 100;

int motorSpeed = 0;
void setup() {
  pinMode(IApin, OUTPUT);
  pinMode(IBpin, OUTPUT);
  Serial.begin(baud);
}

void loop() {
  motorSpeed += 5;
  motorSpeed %= 256;
  motorSpeed = max(motorSpeed, minSpeed);
  Serial.println(motorSpeed);
//  digitalWrite(IApin, HIGH);
  digitalWrite(IApin, motorSpeed);
  digitalWrite(IBpin, LOW);
  delay(delayTime);
}
