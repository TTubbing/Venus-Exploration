#include <Servo.h>                           

int pinLeft = 12;
int pinRight = 13;

int encoder = 0;
int timeturn = 2000;
int correction = -1;

Servo servoLeft;
Servo servoRight;

void setup() {
  
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
}

void loop() {
  int angle;

  forward();
  delay(5000);
  stopp();
  delay(5000);
  backward();
  delay(5000);
  stopp();
  delay(5000);
  angle = 90;
  turnRight(angle);
  delay(5000);
  angle = 90;
  turnLeft(angle);
  delay(5000);
}



void forward(){
  servoLeft.write(180);
  servoRight.write(0);
}

void backward(){
  servoLeft.write(0);
  servoRight.write(180);
}

void stopp(){
  servoLeft.write(90+correction);
  servoRight.write(90+correction);
}

void turnRight(int angle){
  
  int milliseconds;
  
  milliseconds = (360/angle)*timeturn;
  servoLeft.write(180);
  servoRight.write(180);
  delay(milliseconds);
  stopp();
}

void turnLeft(int angle){
  
  int milliseconds;
  
  milliseconds = (angle/360)*timeturn;
  servoLeft.write(0);
  servoRight.write(0);
  delay(milliseconds);
  stopp();
}
