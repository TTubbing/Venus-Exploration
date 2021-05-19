#include <Servo.h>                           

int pinLeft = 12; // Digital pin for the left motor
int pinRight = 13; // Digital pin for the right motor

int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors

Servo servoLeft; // Define servos
Servo servoRight;

void setup_movement() {
  
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
}

void forward(){
  servoLeft.write(180); // Send signal to servo
  servoRight.write(0); // 0 fast backwards, 90 stop, 180 fast forwards.
}

void backward(){
  servoLeft.write(0); // Left is 0 and right 180 because of the way installed
  servoRight.write(180);
}

void stopp(){
  servoLeft.write(90+correction); // Correction is needed to calibrate stop point
  servoRight.write(90+correction);
}

void turn(int angle){
  
  int milliseconds;
  
  milliseconds = (360/angle)*timeturn; // seconds to turn the given angle
  servoLeft.write(180);
  servoRight.write(180);
  delay(milliseconds); // During the delay the motors keep running till next line
  addpath(angle, 0);
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
