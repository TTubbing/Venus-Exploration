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

void GripperOpen(){
  myservo.write(90);
}

void GripperClose(){
  myservo.write(0);
}
