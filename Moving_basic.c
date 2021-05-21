#include <Servo.h>                           

int motorLeft = 12; // Digital pin for the left motor
int motorRight = 13; // Digital pin for the right motor

int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors

Servo LeftmotorServo; // Define servos
Servo RightmotorServo;

void setup_movement() {
  LeftmotorServo.attach(motorLeft);
  RightmotorServo.attach(motorRight);
}

void forward(){
  reset_count();
  LeftmotorServo.write(180); // Send signal to servo
  RightmotorServo.write(0); // 0 fast backwards, 90 stop, 180 fast forwards.
}

void backward(){
  reset_count();
  LeftmotorServo.write(0); // Left is 0 and right 180 because of the way installed
  RightmotorServo.write(180);
}

void stopp(int angle, int count){
  LeftmotorServo.write(90+correction); // Correction is needed to calibrate stop point
  RightmotorServo.write(90+correction);
  addpath(angle, count); //Add angle and distance to path
  reset_count(); //Set encoder values to 0
}

void turn(int angle){
  
  int milliseconds;
  
  milliseconds = (360/angle)*timeturn; // seconds to turn the given angle
  
  if(angle>0){
    LeftmotorServo.write(180);
    RightmotorServo.write(180);
    delay(milliseconds); // During the delay the motors keep running till next line
  }
  
  if(angle<0){
    milliseconds = (angle/360)*timeturn;
    LeftmotorServo.write(0);
    RightmotorServo.write(0);
    delay(milliseconds); //During the delay the motors keep running till next line
  }
  reset_count();
  stopp(angle, 0); //stop and add angle to path
}
