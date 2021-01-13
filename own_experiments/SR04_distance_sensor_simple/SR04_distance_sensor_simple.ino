/**
 * https://toptechboy.com/arduino-tutorial-53-understanding-and-connecting-the-hc-sr04-sensor/
 * Show distance using SR04 sensor with a buzzer to indicate too far
*/

const float tooFar = 10000.;
const float tooClose = -1;
const int baud = 9600;
const int delayTime = 500;

const int echoPin = 11;
const int triggerPin = 12;

void setup() {
  Serial.begin(baud);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // bring the triggerPin low first, then high, then low
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // how long echoPin was on HIGH
  int pingTravelTime = pulseIn(echoPin, HIGH);  
  float distance = toDistance(pingTravelTime);
  if(distance==tooClose){
    ringBuzzer();
  } else {
    silenceBuzzer();
  }
  delay(100);
  Serial.println(String(pingTravelTime) + " ("+String(distance)+")");
}

void ringBuzzer(){
  Serial.println("Ring ring");
}

void silenceBuzzer(){
  Serial.println("Silence");
}

float toDistance(int travelTime) {
  if(travelTime < 195) return -1.;
  if(travelTime > 1200) return tooFar;
  return 0.015504957078815655 * travelTime + 1.808167855636654;
}
