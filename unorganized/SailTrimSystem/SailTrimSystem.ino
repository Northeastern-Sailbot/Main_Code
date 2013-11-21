// Sail Trimming Control System

// lowest and highest readings from the 10bit analog encoder:
const int sensorMin = 0;        // encoder minimum 
const int sensorMax = 1023;     // encoder maximum, 2^10 - 1, verified through experiment

const int encoderTempVals = 5;  // call out number of encoder readings to average

//PWM Servo Control
#include <Servo.h>      // include Arduino Servo library
Servo SailServo;       // create servo object to control Sails
Servo RudderServo;   // create servo object to control Rudder

void setup()
{
  // initialize serial communication:
  Serial.begin(9600);  
  
  SailServo.attach (9);      // attaches the sail servo on pin 9 to the servo object
  RudderServo.attach(10);   // attaches the rudder servo on pin 10 to the servo object  
}

int smoothVals(int vals[])
{
  int total;
  int number = sizeof(vals);  //determine length of array for averaging
  
  for (int i = 0; i < number; i++)  // loop for # of desired encoder values
  {
   total = vals[i] + total;      // continuing adding each array element to total
  }
 return total / number;    // output average of encoder readings
}

void loop() 
{
  int tempVals[encoderTempVals];
  
  for (int i = 0; i < encoderTempVals; i++)  // loop for # of desired encoder values
  {
    tempVals[i] = analogRead(A0);    // create an array of encoder readings
    delay(20);                      // delay between each encoder reading
  }

  int encoderReading = smoothVals(tempVals);    // average encoder readings
  //map the sensor range to a range of four options:
  int range = map(encoderReading, sensorMin, sensorMax, 0, 9);
  
  switch (range) 
{  case 1:    // boat is heading into the no sail zone and must turn left to fill sails
    Serial.println(encoderReading);
    Serial.println("rudder turn boat left");
    RudderServo.writeMicroseconds(2000);        // sets the Rudder servo to turn left 
    SailServo.writeMicroseconds (2225);         // Sail servo position sails all the way in  
    delay(1500);                                // waits for boat to complete turn 
    RudderServo.writeMicroseconds(1500);        // sets the Rudder servo to center position
    break;
  case 2:    // Close Haul 45deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Close Haul sails all the way in");
    SailServo.writeMicroseconds (2225);    // Sail servo position sails all the way in   
    delay(500);                             // waits for the servo to get there
    break;
  case 3:    // Beam Reach 90deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Beam Reach sails 1/2 way out");
    SailServo.writeMicroseconds (1500);   // Sail servo position half way out  
    delay(500);                           // waits for the servo to get there
    break;
  case 4:    // Broad Reach 135deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Broad Reach sails 3/4 way out");
    SailServo.writeMicroseconds (1138);   // Sail servo position sails 3/4 way out  
    delay(500);                           // waits for the servo to get there
    break;
  case 5:    // Run wind coming from directly behind the boat
    Serial.println(encoderReading);
    Serial.println("Run sail all the way out");
    SailServo.writeMicroseconds (775);    // Sail servo position sails all the way out  
    delay(500);                           // waits for the servo to get there
    break;
  case 6:    // Broad Reach 135deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Broad Reach sails 3/4 way out");
    SailServo.writeMicroseconds (1138);   // Sail servo position sails 3/4 way out 
    delay(500);                           // waits for the servo to get there
    break;
  case 7:    // Beam Reach 90deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Beam Reach sails 1/2 way out");
    SailServo.writeMicroseconds (1500);   // Sail servo position sails 3/4 way out 
    delay(500);                           // waits for the servo to get there
    break;
  case 8:    // Close Haul 45deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Close Haul sails all the way in");
    SailServo.writeMicroseconds (2225);    // Sail servo position sails all the way in  
    delay(500);                           // waits for the servo to get there
    break;
  case 9:    // boat is heading into the no sail zone and must turn left to fill sails
    Serial.println(encoderReading);
    Serial.println("rudder turn right");
    RudderServo.writeMicroseconds(1000);      // sets the Rudder servo to turn right 
    SailServo.writeMicroseconds (2225);      // Sail servo position sails all the way in   
    delay(1500);                              // waits for the servo to get there
    RudderServo.writeMicroseconds(1500);    // sets the Rudder servo to center position
    break;
    }
}





