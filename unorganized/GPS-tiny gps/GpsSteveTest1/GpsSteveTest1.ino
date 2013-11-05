#include <SD.h>
const int chipSelect = 4;
String inputString =" ";
boolean stringComplete = false;
String stringGGA = " ";
String stringRMC= " ";
boolean fixComplete=false;
boolean dateComplete=false;


 void serialEvent() {
   while(Serial.available()) {
     char inChar = (char)Serial.read();
     inputString += inChar;
     if (inChar == '\n'){
       stringComplete = true;
     }
   }
 }
 

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  
  Serial.print("Initialzing SD card...");
  pinMode(10, OUTPUT);
  
if (!SD.begin(chipSelect)) {
  Serial.println("Card failed, or not present");
  return;
}

SD.remove("GPSlog.dat");

File dataFile = SD.open("GPSlog.dat", FILE_WRITE);
dataFile.println("dfix,tfix,lat,long,sat,hdop,alt");
dataFile.close();

Serial.println("setup complete\n");

inputString =" ";
stringComplete =false;
}

void loop() {
  if(stringComplete) {
    if(inputString.charAt(4)=='G') {
      stringGGA=inputString;
      fixComplete=true;
    }
    if(inputString.charAt(4)=='M'){
      stringRMC=inputString=" ";
      stringComplete=false;
    }
 }
}


