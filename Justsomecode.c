#include <EnableInterrupt.h>

#include <Servo.h> 

int encoderLeft = 7;
int encoderRight = 8;

int pinLeft = 12; // Digital pin for the left motor
int pinRight = 13; // Digital pin for the right motor
int correction = -1; // Correction for the motors

Servo servoLeft; // Define servos
Servo servoRight;

volatile uint16_t interruptCountLeft = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t interruptCountRight = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t rounds_left = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t rounds_right = 0; // The count will go back to 0 after hitting 65535.

//attach function to get rounds for left encoder
void isrLeft(){
  interruptCountLeft++;
  if (interruptCountLeft >= 8){
    rounds_left++;
    interruptCountLeft = 1;
  }
}

//attach function to get rounds for right encoder
void isrRight(){
  interruptCountRight++;
  if (interruptCountRight >= 8){
    rounds_right++;
    interruptCountRight = 1;
   }
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

void turn(float angle){
  int milliseconds = (((float)angle/(float) 360))*2000; // seconds to turn the given angle
  Serial.print("milliseconds: ");
  Serial.println(milliseconds);
  if(angle>0){
    servoLeft.write(180);
    servoRight.write(180);
    delay(milliseconds); // During the delay the motors keep running till next line
  }
  
  if(angle<0){
    servoLeft.write(0);
    servoRight.write(0);
    delay(milliseconds); //During the delay the motors keep running till next line
  }
  
  stopp(); //stop and add angle to path
  delay(1000);
}

void setup() {
  servoLeft.attach(pinLeft);
  servoRight.attach(pinRight);
  Serial.begin(9600);
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
}

// In the loop we just display interruptCount. The value is updated by the interrupt routine.
void loop() {
  while(rounds_left <= 1){
//    Serial.print("Forward: ");
//    Serial.println(rounds_left, DEC);
    forward();
  }
  stopp();
  delay(1000);
  rounds_left = 0;
  while(rounds_left <= 1){
//    Serial.print("Backward: ");
//    Serial.println(rounds_left, DEC);
    backward();
  }
  stopp();
  delay(1000);
  rounds_left = 0;
  Serial.print("Left: ");
  Serial.println(interruptCountLeft, DEC);
  Serial.print("Right: ");
  Serial.println(interruptCountRight, DEC);
}
