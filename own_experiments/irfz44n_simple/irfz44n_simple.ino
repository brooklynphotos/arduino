/**
 * Controlling speed of motor using IRFZ44N
 * https://dronebotworkshop.com/transistors-mosfets/
 * https://www.instructables.com/Mosfet-Qith-Arduino-IRFZ44N-IRLZ44N-IRF530N/
 */
const int mosfetPin = 6;
const int potPin = A5;
int delayTime = 100;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(mosfetPin, OUTPUT);
}

void loop() {
  int potReading = analogRead(potPin);
  Serial.println("Pot reading: "+String(potReading));
  int motorSpeed = map(potReading, 0, 1023, 0, 255);
  Serial.println("Speed: "+String(motorSpeed));
  analogWrite(mosfetPin, motorSpeed);
  motorSpeed++;
  delay(delayTime);
}
