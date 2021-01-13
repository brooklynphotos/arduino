
/**
 * Based on: https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/#1
*/

const int baud = 9600;

// OLED
const int IR_pin = 8;

void setup() {
  Serial.begin(baud);
  pinMode(IR_pin, INPUT);
}

void loop() {
  String msg = digitalRead(IR_pin)==LOW ? "Obstacle" : "None";
  Serial.println(msg);
  delay(100);
}
