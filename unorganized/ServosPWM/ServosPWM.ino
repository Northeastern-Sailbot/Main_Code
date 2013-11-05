//PWM Servo Control

#include <Servo.h>

Servo SailServo;

void setup()
{
  SailServo.attach (9);  //PWM pin
}

void loop()
{
  SailServo.writeMicroseconds (1500);  //center servo
  delay(1000); 
  
  SailServo.writeMicroseconds (1000); //make servo go left
  delay(1000); 
  
  SailServo.writeMicroseconds (2000); //make servo go right
  delay(1000); 
}


