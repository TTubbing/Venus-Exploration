#include <Servo.h>
Servo myservo;
#define servoPin 10

void setup() {
  myservo.attach(servoPin);
}

void loop() {
  GripperOpen();
  delay(1000);
  GripperClose();
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
