// Sail Trim Control System

// lowest and highest readings from the 10bit encoder:
const int sensorMin = 0;      // encoder minimum 
const int sensorMax = 1023;    // encoder maximum, 2^10-1, verified through experiment

#include <SoftwareServo.h> 

SoftwareServo MainSailServo;  // create servo object to control Main Sail
SoftwareServo RudderServo;  // create servo object to control Rudder

void setup()
{
  // initialize serial communication:
  Serial.begin(9600);  
  
  MainSailServo.attach(2);  // attaches the main sail servo on pin 2 to the servo object
  RudderServo.attach(3);  // attaches the rudder servo on pin 3 to the servo object  
}

void loop() {
  // read the sensor:
  int encoderReading = analogRead(A0);
  // map the sensor range to a range of four options:
  int range = map(encoderReading, sensorMin, sensorMax, 0, 9);

  // do something different depending on the 
  // range value:
  switch (range) {
  case 1:    // boat is heading into the no sail zone and must turn left to fill sails
    Serial.println(encoderReading);
    Serial.println("rudder turn boat left");
    RudderServo.write(90);             // sets the Rudder servo to turn left 
    delay(15);                           // waits for the servo to get there
    MainSailServo.write(90);             //Main Sail servo position sails all the way in  
    delay(15);                           // waits for the servo to get there
    break;
  case 2:    // Close Haul 45deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Close Haul sails all the way in");
    MainSailServo.write(90);             //Main Sail servo position sails all the way in  
    delay(15);                           // waits for the servo to get there
    break;
  case 3:    // Beam Reach 90deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Beam Reach sails 1/2 way out");
    MainSailServo.write(135);             //Main Sail servo position half way out  
    delay(15);                           // waits for the servo to get there
    break;
  case 4:    // Broad Reach 135deg to wind coming across starboard side of sailboat
    Serial.println(encoderReading);
    Serial.println("Broad Reach sails 3/4 way out");
    MainSailServo.write(158);             //Main Sail servo position sails 3/4 way out  
    delay(15);                           // waits for the servo to get there
    break;
  case 5:    // Run wind coming from directly behind the boat
    Serial.println(encoderReading);
    Serial.println("Run sail all the way out");
    MainSailServo.write(180);             //Main Sail servo position sails all the way out  
    delay(15);                           // waits for the servo to get there
    break;
  case 6:    // Broad Reach 135deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Broad Reach sails 3/4 way out");
    MainSailServo.write(22);             //Main Sail servo position sails 3/4 way out  
    delay(15);                           // waits for the servo to get there
    break;
  case 7:    // Beam Reach 90deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Beam Reach sails 1/2 way out");
    MainSailServo.write(45);             //Main Sail servo position sails half the way out 
    delay(15);                           // waits for the servo to get there
    break;
  case 8:    // Close Haul 45deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Close Haul sails all the way in");
    MainSailServo.write(90);             //Main Sail servo position sails all the way in  
    delay(15);                           // waits for the servo to get there
    break;
  case 9:    // boat is heading into the no sail zone and must turn left to fill sails
    Serial.println(encoderReading);
    Serial.println("rudder turn right");
    RudderServo.write(0);               // sets the Rudder servo to turn right 
    delay(15);                           // waits for the servo to get there
    MainSailServo.write(90);             //Main Sail servo position sails all the way in  
    delay(15);                           // waits for the servo to get there
    break;
    } 
  delay(50);        // delay in between reads for stability
}





