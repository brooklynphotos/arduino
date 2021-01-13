
/**
 * Assembly of different sensors and outputs to make this car move
*/

#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int baud = 9600;
const int loopWait = 100;

// switch
const int switchPin = 2;
bool on = false;

// passive buzzer
const int buzzerPin = 3;

// ultrasound sensor
const int triggerPin = 4;
const int echoPin = 5;
const int maxDistance = 400;
const int minDistance = 2;
NewPing sonar(triggerPin, echoPin, maxDistance);

// IR Obstacle sensors
const int IRLeftPin = 6;
const int IRRightPin = 7;

// LEDs
const int leftLEDPins[] = {8, 9, 10};
const int rightLEDPins[] = {13, 11, 12};
#define RED 0
#define GREEN 1
#define BLUE 2

// motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

// motion constants
const int SAFE_DISTANCE = 10;
const int MAX_SPEED = 255;
const int MIN_SPEED = 100;

// globals for the state of the car
int frontDistance = 0;

void setup() {
  Serial.begin(baud);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(IRLeftPin, INPUT);
  pinMode(IRRightPin, INPUT);
  for(int i=0;i<3;i++){
    pinMode(leftLEDPins[i], OUTPUT);
    pinMode(rightLEDPins[i], OUTPUT);
  }

  // start the motor
  AFMS.begin();
}

void startupMusic(int count, int silentTime){
  for(int i=0;i<count;i++){
    ringBuzzer(1000, 1);
    delay(silentTime);
  }  
  ringBuzzer(1000, 2);
}

void shutdownMusic(int count, int silentTime){
  ringBuzzer(1000, 2);
  for(int i=0;i<count;i++){
    ringBuzzer(1000, 1);
    delay(silentTime);
  }  
}

void loop() {
  Serial.println("Car on: "+String(on));
  byte switchVal = digitalRead(switchPin);
  // is the switch pressed?
  if(switchVal==0){
    on = !on;
    if(on){
      startupMusic(2, 1000);
    } else {
      shutdownMusic(2, 1000);
    }
  }
  if(!on){
   haltCar();
   on = false;
   return;
  }
  // the car is still running, so let's see what to do next
  float frontDistance = getFrontDistance();
  if(frontDistance <= minDistance){
    Serial.println("Distance is out of range");
    haltCar();
    ringBuzzer(100, 2);
  }else{
    Serial.println("Distance = " + String(frontDistance) + " cm");
    if(frontDistance<SAFE_DISTANCE){
      haltCar();
      ringBuzzer(200, 2);
    }
  }
  if(digitalRead(IRLeftPin) != LOW){
    Serial.println("Left is over a cliff");
    brakeCar();
    ringBuzzer(500, 2);
  }
  if(digitalRead(IRRightPin) != LOW){
    Serial.println("Right is over a cliff");
    brakeCar();
    ringBuzzer(800, 2);
  }
  if(on){
    runCar();
  }
  delay(loopWait);
}

float getFrontDistance(){  
  int attemptCount = 5;
  float attempts[5];
  for(int i=0;i<attemptCount;i++){
    float d = getDistance(sonar);
    for(int i=0;i<attemptCount;i++){
      float v = attempts[i];
      if(v==0){
        attempts[i] = d;
        break; // we are done
      }else{
        if(d<v){
          for(int j=i+1;j<attemptCount;j++){
            attempts[j] = attempts[j-1];
          }
          attempts[i] = d;
        }
      }
    }
  }
  float distanceSum = 0;
  for(int i=1;i<attemptCount-1;i++){
    distanceSum += attempts[i];
  }
  return distanceSum / attemptCount;
}

float getDistance(NewPing sonarObj){
    float duration = sonarObj.ping();
    return (duration / 2) * 0.0343;
}

void lookForLeeway(){
  float minDistance = 100; // looking for something at least these many cm away
  rotateCar();
  while(true){
    float dist = getFrontDistance();
    if(dist>=minDistance){
      stopCar();
      return;
    }
  }
}

void rotateCar(){
  Serial.println("Turning car");
  lightLED(leftLEDPins, GREEN);
  lightLED(rightLEDPins, GREEN);
  motor1->setSpeed(MIN_SPEED);
  motor2->setSpeed(MIN_SPEED);
  motor1->run(FORWARD);
  motor2->run(BACKWARD);
}

void runCar(){
  Serial.println("Running car");
  lightLED(leftLEDPins, GREEN);
  lightLED(rightLEDPins, GREEN);
  motor1->setSpeed(MAX_SPEED);
  motor2->setSpeed(MAX_SPEED);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
}

void stopCar(){
  Serial.println("Stopped car");
  lightLED(leftLEDPins, RED);
  lightLED(rightLEDPins, RED);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}

void haltCar(){
  stopCar();
  on = false;
}

void brakeCar(){
  Serial.println("Braking car");
  lightLED(leftLEDPins, BLUE);
  lightLED(rightLEDPins, BLUE);
  motor1->run(BACKWARD);
  motor2->run(BACKWARD);
  delay(300);
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}

void lightLED(int pins[], int color){
  for(int i=0;i<3;i++){
    digitalWrite(pins[i], i==color ? HIGH: LOW);
  }
}

void ringBuzzer(int herz, int duration){
  for(int i=0;i<(100000.0*duration/herz);i++){
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(herz);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(herz);
  }
}
