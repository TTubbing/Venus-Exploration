#include <Servo.h>                           

int pinLeft = 12; // Digital pin for the left motor
int pinRight = 13; // Digital pin for the right motor

int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors

Servo servoLeft; // Define servos
Servo servoRight;

void setup() {
  
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
}

void loop() {
  int angle; // Define angle which robot has to turn

  forward(); // Move forwards
  delay(5000); // Keep moving forwards during delay
  stopp(); // Stop moving
  delay(5000);
  backward(); //Move backwards
  delay(5000);
  stopp();
  delay(5000);
  angle = 90;
  turnRight(angle); // Robot turns to the right (90 degree)
  delay(5000);
  angle = 90;
  turnLeft(angle); // Robot turns to the left (90 degree)
  delay(5000);
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

void turnRight(int angle){
  
  int milliseconds;
  
  milliseconds = (360/angle)*timeturn; // seconds to turn the given angle
  servoLeft.write(180);
  servoRight.write(180);
  delay(milliseconds); // During the delay the motors keep running till next line
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
