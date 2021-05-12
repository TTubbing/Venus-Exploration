#include <SoftwareSerial.h>
SoftwareSerial xbee(0, 1); // RX, TX
int c;
int five = 5;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
}

void loop() {
  
 if(xbee.available() > 0){
    c = xbee.read();
    Serial.print(c);
    //or
    //xbee.print(five);
    //delay(500);
    
  }
  
   if(Serial.available() > 0){
      c = Serial.read();
      Serial.print(c);
      //or
      //Serial.print(five);
      //delay(500);
    }
}
