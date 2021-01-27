/**
   https://toptechboy.com/arduino-tutorial-64-understanding-and-using-the-infrared-ir-remote-to-control-a-project/
   Turn on LEDs using IR Remote
*/

#include <IRremote.h>

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
const int delayTime = 1000;

void setup() {
  Serial.begin(baud);
  IR.enableIRIn();
}

void loop() {
  while (IR.decode(&cmd) == 0);
  Serial.println(cmd.value, HEX);
  delay(delayTime);
  IR.resume();
}
