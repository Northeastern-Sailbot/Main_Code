#include<String.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

TinyGPS gps;

int on_off = 13;
int rxPin= 0;
int txPin = 1;
SoftwareSerial mySerial(rxPin, txPin);

void setup(){
   pinMode(on_off, OUTPUT);
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   Serial.begin(38400);
   mySerial.begin(4800);
   digitalWrite(on_off, HIGH);
   delay(105);
   digitalWrite(on_off, LOW);
   mySerial.write("$GLL");
}

void loop() {
    Serial.println(mySerial.read());
    //mySerial.write(mySerial.read());
}
