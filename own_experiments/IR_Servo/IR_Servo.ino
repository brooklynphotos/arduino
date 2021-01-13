/**
   https://toptechboy.com/arduino-tutorial-64-understanding-and-using-the-infrared-ir-remote-to-control-a-project/
   Turn on LEDs using IR Remote
*/

#include <IRremote.h>
#include <Servo.h>


#define POWER 0xFFA25D
#define HELD_DOWN 0xFFFFFFFF
#define VOL_PLUS 0xFF629D
#define STOP 0xFFE21D
#define BEGINNING 0xFF22DD
#define END 0xFFC23D
#define PLAY_PAUSE 0xFF02FD
#define DOWN 0xFFE01F
#define UP 0xFF906F
#define ZERO 0xFF6897
#define ONE 0xFF30CF
#define TWO 0xFF18E7
#define THREE 0xFF7A85
#define FOUR 0xFF10EF
#define FIVE 0xFF38C7
#define SIX 0xFF5AA5
#define SEVEN 0xFF42BD
#define EIGHT 0xFF4AB5
#define NINE 0xFF52AD
#define EQUALIZER 0xFF9867
#define ST_RPT 0xFFB04F

const int IRPin = 9;
IRrecv IR(IRPin);
decode_results cmd;

const int baud = 9600;
const int delayTime = 200;

// LED pins
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 3;

// buzzer
const int buzzerPin = 2;
const int buzzerDuration = 100;

// servo
const int servoPin = 11;
int servoPosition = 0; // where it is now
// virtual object for servo
Servo servo;

void setup() {
  Serial.begin(baud);
  pinMode(buzzerPin, OUTPUT);
  IR.enableIRIn();
  servo.attach(servoPin); 
}

void loop() {
  while (IR.decode(&cmd) == 0);
  switch (cmd.value) {
    case POWER:
      beepBuzzer();
      break;
    case UP:
    case DOWN:
    case STOP:
      moveServo(cmd.value);
      break;
    default:
      turnOnLED(cmd.value);
  }
  delay(delayTime);
  Serial.println(cmd.value, HEX);
  IR.resume();
}

void moveServo(long d){
  Serial.println("Servo direction: "+String(d, HEX));
  Serial.println("Servo direction: "+String(STOP, HEX));
  if(d==STOP){
    servoPosition = 0;
  }else{
    int servoDirection = 1;
    if(d==DOWN){
      servoDirection = -1;
    }
    servoPosition += servoDirection * 10;
    servoPosition = max(servoPosition, 0);
    servoPosition %= 180;
  }
  Serial.println("Servo position: " + String(servoPosition));
  servo.write(servoPosition);

}

void turnOnLED(int buttonVal){
  switch(buttonVal){
    case ZERO:
      lightLED(0,0,0);
      break;
    case ONE:
      lightLED(255, 0, 0);
      break;
     case TWO:
      lightLED(0, 255, 0);
      break;
     case THREE:
      lightLED(0, 0, 255);
      break;
     default:
      lightLED(255, 255, 255);
  }
}

void lightLED(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  Serial.println("Color: ("+String(r)+","+String(g)+","+String(b)+")");
}

void beepBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(buzzerDuration);
  digitalWrite(buzzerPin, LOW);
}
