#include <Servo.h>
Servo myservo;
#define servoPin 10

void setup() {
  myservo.attach(servoPin);
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
  myservo.write(90);
}

void ServoToRight(){
  myservo.write(0);
}

void ServoToLeft(){
  myservo.write(180);
}
