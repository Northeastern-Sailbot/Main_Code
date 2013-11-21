//Tacking Function

// lowest and highest readings from the 10bit analog encoder:
const int sensorMin = 0;        // encoder minimum 
const int sensorMax = 1023;     // encoder maximum, 2^10 - 1, verified through experiment
const int encoderTempVals = 5;  // call out number of encoder readings to average
//PWM Servo Control
#include <Servo.h>      // include Arduino Servo library
#include <PS3BT.h>      // include PS3 library
Servo SailServo;       // create servo object to control Sails
Servo RudderServo;   // create servo object to control Rudder

USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

void setup()
{
  Serial.begin(115200);    // initialize serial communication:
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
  SailServo.attach (9);      // attaches the sail servo on pin 9 to the servo object
  RudderServo.attach(10);   // attaches the rudder servo on pin 10 to the servo object  
}

void loop()
{
  
  int wind_position = Wind_Reading();
  
  
  
  Usb.Task();
  if(PS3.PS3Connected || PS3.PS3NavigationConnected) 
    {
    if(PS3.getButtonClick(CROSS))
        {
          Serial.println("Tacking");
          SailServo.writeMicroseconds(1825);
          delay(500);
          Serial.print(F("\r\nCross"));
          tacking(wind_position);
          delay(1500);
        }
     if(PS3.getAnalogButton(L2))
     {
      Serial.print(F("\r\nL2: ")); 
      Serial.print(PS3.getAnalogButton(L2));
      
      int L_2 = map(PS3.getAnalogButton(L2), 0, 256, 1000, 1825);
      
      SailServo.writeMicroseconds(L_2);
      delay(200);
     }
           
      
     else
     {
       RudderServo.writeMicroseconds(1500);
     }
    }
    
    
  

  
  int wind = map(wind_position, 511, 1023, 511, 0);
}







//Function 1
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


//Tacking Function
void tacking(int wind_position)
{
  int windposition= analogRead(A0);
  
  
  if (windposition < 512) //Starboard Tack
  {
    for (int RudderCompensation = 1500; RudderCompensation > 1000; RudderCompensation-100)
    {
      RudderServo.writeMicroseconds(RudderCompensation);
      windposition = Wind_Reading();
      delay(250);
      }
    }
  else //Port Tack
  {
    for (int RudderCompensation = 1500; RudderCompensation < 2000; RudderCompensation+100)
    {
      RudderServo.writeMicroseconds(RudderCompensation);
      windposition = Wind_Reading();
      delay(250);
      }
    }
    
  RudderServo.writeMicroseconds(1500);
  windposition = Wind_Reading();
  SailTrim(windposition);
  
}
  

//Sail Trim Function
void SailTrim(int encoderReading)
{
   
  int RudderCompensation;
  int windposition = analogRead(A0);
  if (windposition < 512)
  {
    RudderCompensation = 2000;
  }
  else
  {
    RudderCompensation = 1000;
  }

  
  //map the sensor range to a range of four options:
  int range = map(encoderReading, 511, sensorMax, 0, 5);
  
  switch (range) 
{  
  case 0:    // Run wind coming from directly behind the boat
    Serial.println(encoderReading);
    Serial.println("Run sail all the way out");
    SailServo.writeMicroseconds (1000);    // Sail servo position sails all the way out  
    delay(500);                           // waits for the servo to get there
    break;
  case 1:    // Broad Reach 135deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Broad Reach sails 3/4 way out");
    SailServo.writeMicroseconds (1138);   // Sail servo position sails 3/4 way out 
    delay(500);                           // waits for the servo to get there
    break;
  case 2:    // Beam Reach 90deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Beam Reach sails 1/2 way out");
    SailServo.writeMicroseconds (1550);   // Sail servo position sails 3/4 way out 
    delay(500);                           // waits for the servo to get there
    break;
  case 3:    // Close Haul 45deg to wind coming across port side of sailboat
    Serial.println(encoderReading);
    Serial.println("Close Haul sails all the way in");
    SailServo.writeMicroseconds (1825);    // Sail servo position sails all the way in  
    delay(500);                           // waits for the servo to get there
    break;
  case 4:    // boat is heading into the no sail zone and must turn left to fill sails
    Serial.println(encoderReading);
    Serial.println("rudder turn right");
    RudderServo.writeMicroseconds(RudderCompensation);      // sets the Rudder servo to turn right 
    SailServo.writeMicroseconds (2100);      // Sail servo position sails all the way in   
    delay(1500);                              // waits for the servo to get there
    RudderServo.writeMicroseconds(1500);    // sets the Rudder servo to center position
    break;
    }
}

int Wind_Reading () //Wind direction encoder reading
{
  int tempVals[encoderTempVals];
  int basevalue=analogRead(A0);
  for (int i = 0; i < encoderTempVals; i++)  // loop for # of desired encoder values
  {
    basevalue=analogRead(A0);
    if(basevalue < 512)
    {
      basevalue=map(basevalue, 0, 511, 1023, 511);
    }
    else
    {     }
    tempVals[i] = basevalue;    // create an array of encoder readings
    delay(20);                      // delay between each encoder reading
  }
  
  int encoderReading = smoothVals(tempVals);
  
  return encoderReading;
}
