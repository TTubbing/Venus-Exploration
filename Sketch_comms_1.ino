#include <SoftwareSerial.h>
SoftwareSerial xbee(0, 1); // RX, TX
char c;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
}

void loop() {
  
 if(xbee.available() > 0){
    //c = xbee.read();
    //Serial.print(c);
    //or
    xbee.print('M');
    delay(1000);
    
  }
  
   if(Serial.available() > 0){
      //c = Serial.read();
      //Serial.print(c);
      //or
      Serial.print('M');
      delay(1000);
    }
}
