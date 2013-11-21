/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or 
 send me an e-mail:  kristianl@tkjelectronics.com
 */
#include <Servo.h>      // include Arduino Servo library
#include <PS3BT.h>
USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd,0x00,0x15,0x83,0x3D,0x0A,0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

boolean printTemperature;
boolean printAngle;
Servo SailServo;       // create servo object to control Sails
Servo RudderServo;
int RudderCompensation=2000;
int servoconversion;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  SailServo.attach (9); 
  RudderServo.attach (10);
}
void loop() {
  Usb.Task();

  if(PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if(PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: ")); 
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: ")); 
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if(!PS3.PS3NavigationConnected) {
        Serial.print(F("\tRightHatX: ")); 
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: ")); 
        Serial.print(PS3.getAnalogHat(RightHatY)*4+1000);
        SailServo.writeMicroseconds (PS3.getAnalogHat(RightHatX)*4+1000);
        delay(250);

        //if (PS3.getAnalogHat(RightHatX) <50)
                    
      }
    }
       
       /*
        int range = map(PS3.getAnalogHat(RightHatX), 0, 255, 0, 5);     
        switch (range) 
        {  
        case 0:    // Run wind coming from directly behind the boat
          RudderServo.writeMicroseconds (1000);    // Sail servo position sails all the way out  
          delay(250);                              // waits for the servo to get there
          break;
        case 1:    // Broad Reach 135deg to wind coming across port side of sailboat
          SailServo.writeMicroseconds (1138);   // Sail servo position sails 3/4 way out 
          delay(250);                              // waits for the servo to get there
          break;
        case 2:    // Beam Reach 90deg to wind coming across port side of sailboat
          SailServo.writeMicroseconds (1550);   // Sail servo position sails 3/4 way out 
          delay(250);                              // waits for the servo to get there
          break;
        case 3:    // Close Haul 45deg to wind coming across port side of sailboat
          RudderServo.writeMicroseconds (1825);    // Sail servo position sails all the way in  
          delay(250);                              // waits for the servo to get there
          break;
        case 4:    // boat is heading into the no sail zone and must turn left to fill sails
          RudderServo.writeMicroseconds(RudderCompensation);      // sets the Rudder servo to turn right 
          //SailServo.writeMicroseconds (2100);      // Sail servo position sails all the way in   
          delay(250);                              // waits for the servo to get there
          RudderServo.writeMicroseconds(1500);    // sets the Rudder servo to center position
          break;
        }
      }      
    }




 */

  







    //Analog button values can be read from almost all buttons
    if(PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: ")); 
      Serial.print(PS3.getAnalogButton(L2));
      if(!PS3.PS3NavigationConnected) {
        Serial.print(F("\tR2: ")); 
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
    if(PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    } 
    else {
      if(PS3.getButtonClick(TRIANGLE))
        {
          Serial.print(F("\r\nTraingle"));
          Serial.println("Run sail all the way out");
          SailServo.writeMicroseconds (1000);    // Sail servo position sails all the way out  
          delay(500);         // waits for the servo to get there
        }
      if(PS3.getButtonClick(CIRCLE))
        {
          Serial.print(F("\r\nCircle"));
          Serial.println("Run sail all the way out");
          SailServo.writeMicroseconds (1000);    // Sail servo position sails all the way out  
          delay(500);                           // waits for the servo to get there
        }
      if(PS3.getButtonClick(CROSS))
        {
          Serial.println("Beam Reach sails 1/2 way out");
          SailServo.writeMicroseconds (1550);   // Sail servo position sails 3/4 way out 
          delay(500);                           // waits for the servo to get there
          Serial.print(F("\r\nCross"));
        }
      if(PS3.getButtonClick(SQUARE))
        {
            Serial.println("Close Haul sails all the way in");
            SailServo.writeMicroseconds (1825);    // Sail servo position sails all the way in  
            delay(500);                           // waits for the servo to get there
            Serial.print(F("\r\nSquare"));
        }

      if(PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));          
        if(PS3.PS3Connected) {
          PS3.setAllOff();
          PS3.setLedOn(LED4);
        }
      } 
      if(PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if(PS3.PS3Connected) {
          PS3.setAllOff();
          PS3.setLedOn(LED1); 
        }         
      } 
      if(PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if(PS3.PS3Connected) {
          PS3.setAllOff();
          PS3.setLedOn(LED2);          
        }
      } 
      if(PS3.getButtonClick(LEFT)) {          
        Serial.print(F("\r\nLeft"));          
        if(PS3.PS3Connected) {
          PS3.setAllOff();         
          PS3.setLedOn(LED3);            
        }         
      } 

      if(PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));  
      if(PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3")); 
      if(PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));             
      if(PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if(PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - ")); 
        Serial.print(PS3.getStatusString());        
      } 
      if(PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));              
        printAngle = !printAngle;
      }                           
    }
    if(printAngle) {
      Serial.print(F("\r\nPitch: "));               
      Serial.print(PS3.getAngle(Pitch));                  
      Serial.print(F("\tRoll: ")); 
      Serial.print(PS3.getAngle(Roll));
    }
  }
  else if(PS3.PS3MoveConnected) {
    if(PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: ")); 
      Serial.print(PS3.getAnalogButton(T)); 
    } 
    if(PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    } 
    else {
      if(PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      } 
      if(PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;                          
      } 
      if(PS3.getButtonClick(TRIANGLE)) {            
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      } 
      if(PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      } 
      if(PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      } 
      if(PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      } 
      if(PS3.getButtonClick(MOVE)) {     
        PS3.moveSetBulb(Off);                        
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - ")); 
        Serial.print(PS3.getStatusString());
      }
    }
    if(printAngle) {
      Serial.print(F("\r\nPitch: "));               
      Serial.print(PS3.getAngle(Pitch));                  
      Serial.print(F("\tRoll: ")); 
      Serial.print(PS3.getAngle(Roll));
    }
    else if(printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
}
