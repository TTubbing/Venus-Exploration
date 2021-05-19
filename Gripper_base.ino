/*
Gripper has to close when they find a rock
The rock in this case has already been detected and the robot needs to:
open grippers
drive forward for certain amount of time
close grippers well

*/
#include <Servo.h>
#define servoPin 10
int distance_for_gripper = 10;
int pinLeft = 12; // Digital pin for the left motor
int pinRight = 13; // Digital pin for the right motor

int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors


Servo myservo;
Servo servoLeft; // Define servos
Servo servoRight;

void setup_movement() {
  
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
}

void setup() {
  myservo.attach(servoPin);
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
}

void GripperOpen(){
  myservo.write(90);
}

void GripperClose(){
  myservo.write(160);
}

void forward(){
  servoLeft.write(180); // Send signal to servo
  servoRight.write(0); // 0 fast backwards, 90 stop, 180 fast forwards.
}

void backward(){
  servoLeft.write(0); // Left is 0 and right 180 because of the way installed
  servoRight.write(180);
}

void stopp(int angle, int distance){
  servoLeft.write(90+correction); // Correction is needed to calibrate stop point
  servoRight.write(90+correction);
}

void pick_up_rock() {
GripperOpen();
//forward();
delay(1000);
//stopp(0,distance_for_gripper);
//stopp(0,distance_for_gripper);
//stopp(0,distance_for_gripper);
//stopp(0,distance_for_gripper);
//stopp(0,distance_for_gripper);
GripperClose();
}

void loop() {
  pick_up_rock();
  delay(5000);
}
