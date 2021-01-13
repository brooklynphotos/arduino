/**
 * https://www.instructables.com/Arduino-How-to-Control-DC-Motors-With-L293D-Motor-/
 * Two DCs. 
 * For L298N module: https://dronebotworkshop.com/dc-motors-l298n-h-bridge/
 * 
 * Notes
 * 1. Need at least 6V input for two motors
 * 2. If External input is not provided, the Vcc2 from Arduino is used, so be careful
 * 3. This also works for the L298N breakout module
 */

const int baud = 9600;
const int leftDriverPin = 9;
const int leftDirPin1 = 12;
const int leftDirPin2 = 8;
const int rightDriverPin = 3;
const int rightDirPin1 = 4;
const int rightDirPin2 = 2;

const int minimumSpeed = 100;

// start with reverse so on the first loop iteration we are back on +1
int motorDir = -1;

int currentSpeed = minimumSpeed;

void setup() {
  pinMode(leftDriverPin, OUTPUT);
  pinMode(leftDirPin1, OUTPUT);
  pinMode(leftDirPin2, OUTPUT);
  pinMode(rightDriverPin, OUTPUT);
  pinMode(rightDirPin1, OUTPUT);
  pinMode(rightDirPin2, OUTPUT);
  Serial.begin(baud);
}

void loop() {
  currentSpeed = max(minimumSpeed, currentSpeed % 256);
  Serial.println("Current speed: "+String(currentSpeed));
  if(currentSpeed==minimumSpeed){
    motorDir *= -1;
  }
  
  digitalWrite(leftDirPin1, motorDir==1 ? HIGH : LOW);
  digitalWrite(leftDirPin2, motorDir==1 ? LOW : HIGH);
  analogWrite(leftDriverPin, 255);

  digitalWrite(rightDirPin1, motorDir==1 ? HIGH : LOW);
  digitalWrite(rightDirPin2, motorDir==1 ? LOW : HIGH);
  analogWrite(rightDriverPin, 255);

  currentSpeed += 10;
  delay(1000);
}
