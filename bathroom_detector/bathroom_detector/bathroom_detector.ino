/**
 * Testing out laser
 * https://arduinomodules.info/ky-008-laser-transmitter-module/
 */

const int photoReaderPin = A0;
const int pirPin = 12;
const int buzzerPin = 7;
const int pirLED = 8;
const int photoReaderLED = 9;

const int delayTime = 200;

const int LIMIT = 270;
const bool DEBUG = false;
const unsigned long absenceTolerance = 3 * 60; // number of seconds

unsigned long lastActive = millis() / 1000L;

bool previousLightOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(photoReaderPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int level = analogRead(photoReaderPin);
  if(DEBUG) Serial.println(level);
  bool lightOn = level > LIMIT;
  if(!lightOn){
    digitalWrite(photoReaderLED, LOW);
    if(DEBUG) Serial.println("Dark");
  } else {
    digitalWrite(photoReaderLED, HIGH);
    Serial.println("Bright");
  }
  int pirVal = digitalRead(pirPin);
  if(pirVal==HIGH){
    Serial.println("present");
    lastActive = millis() / 1000L;
    digitalWrite(pirLED, HIGH);
  }else{
    if(DEBUG) Serial.println("absent");
    digitalWrite(pirLED, LOW);
  }
  // if the light was turned on then someone came in
  // the PIR sensor might not right away detected it
  if(!previousLightOn && lightOn){
    lastActive = millis() / 1000L;
  }
  previousLightOn = lightOn;
  
  unsigned long currentTime = millis() / 1000L;
  unsigned long elapsedTime = currentTime - lastActive;
  // light is on, is someone around?
  if(lightOn){
    int remainingTime = absenceTolerance - elapsedTime;
    Serial.println("Light on, remaining time: "+String(remainingTime));
    if(remainingTime <= 0){
      Serial.println("Turn off light! It has been "+String(elapsedTime)+" seconds");
      ringBuzzer();
    }
  }
  
  delay(delayTime);
}

void ringBuzzer(){
  for(int i=0;i<1000;i++){
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(100);
  }
}
