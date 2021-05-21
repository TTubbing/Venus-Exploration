/*
Gripper has to close when they find a rock
The rock in this case has already been detected and the robot needs to:
open grippers
drive forward for certain amount of time
close grippers well

*/
#include <Servo.h>
#define GripperservoPin 10
int distance_for_gripper = 10;
int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors

Servo gripperservo;

void setup() {
  myservo.attach(GripperservoPin);
  servoLeft.attach(pinLeft);
}

void GripperOpen(){
  gripperservo.write(90);
}

void GripperClose(){
  gripperservo.write(160);
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
