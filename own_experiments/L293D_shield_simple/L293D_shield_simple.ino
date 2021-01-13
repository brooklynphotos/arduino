/**
 * https://lastminuteengineers.com/l293d-motor-driver-shield-arduino-tutorial/
 */
#include <AFMotor.h>

AF_DCMotor motor(4);

void setup() 
{
  //Set initial speed of the motor & stop
  motor.setSpeed(255);
  motor.run(RELEASE);
}

void loop() 
{
  uint8_t i;

  // Turn on motor
  motor.run(FORWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motor.setSpeed(i);  
    delay(10);
  }
  
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motor.setSpeed(i);  
    delay(10);
  }

  // Now change motor direction
  motor.run(BACKWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motor.setSpeed(i);  
    delay(10);
  }

  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motor.setSpeed(i);  
    delay(10);
  }

  // Now turn off motor
  motor.run(RELEASE);
  delay(1000);
}
