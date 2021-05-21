#include <Servo.h>
Servo USservo;
#define USservo 11

void setup() {
  USservo.attach(USservo);
}

void loop() {
  ServoToFront();
  delay(1000);
  ServoToLeft();
  delay(1000);
  ServoToRight();
  delay(1000);
}

void ServoToFront(){
  USservo.write(90);
}

void ServoToRight(){
  USservo.write(0);
}

void ServoToLeft(){
  USservo.write(180);
}
