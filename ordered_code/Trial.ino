#include <Servo.h>
Servo USservo;
Servo LeftmotorServo; // Define servos
Servo RightmotorServo;
#define servoPin 11
#define error_margin 2
#define max_distance 300
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#include <EnableInterrupt.h>

int encoderLeft = 7;
int encoderRight = 8;
volatile int count_left = 0;
volatile int count_right = 0;
float diameter_wheel = 6.5;
float distance_left, distance_right = 0;
const float Pi = 3.14159;

void setup_encoders() {
  Serial.begin(115200);
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
}

void reset_count(){ //reset distance count
  count_left = 0;
  count_right = 0;
}

void calculate_distance(){ //calculate distance travelled
  distance_left = (count_left/9)*Pi*diameter_wheel);
  distance_right = (count_right/9)*Pi*diameter_wheel);
}

//attach function to get rounds for left encoder
void isrLeft(){
  count_left++;
}

//attach function to get rounds for right encoder
void isrRight(){
  count_right++;
}

int update_interval = 300; // interval between measurements
int distance_to_mountain = 10; // ditance to the mountain
int width = 10; // width of search area to find the montain again
int out_of_sight; // minimal distance till mountain is out of sight
int error_driving_parallel_to_mountain = 4;

volatile uint16_t interruptCountLeft = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t interruptCountRight = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t rounds_left = 0; // The count will go back to 0 after hitting 65535.
volatile uint16_t rounds_right = 0; // The count will go back to 0 after hitting 65535.

int encoderLeft = 7;
int encoderRight = 8;

int motorLeft = 12; // Digital pin for the left motor
int motorRight = 13; // Digital pin for the right motor
int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors


const int pingPin = 9; //pingpin declaration (on input 9)
long distance4, distance3; //distances declaration, distance 4 is the distance from the object to the upper sensor and distance 3 is the distance from the object to the lower sensor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  LeftmotorServo.attach(motorLeft);
  RightmotorServo.attach(motorRight);
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
}                         

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

void setup_USservo() {
  USservo.attach(servoPin);
}

int IR1(){
  return 0;
}

int IR2(){
  return 0;
}

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



void turn(float angle){
  int milliseconds = (((float)angle/(float) 360))*2000; // seconds to turn the given angle
  Serial.print("milliseconds: ");
  Serial.println(milliseconds);
  if(angle>0){
    servoLeft.write(180);
    RightmotorServo.write(180);
    delay(milliseconds); // During the delay the motors keep running till next line
  }
  
  if(angle<0){
    servoLeft.write(0);
    RightmotorServo.write(0);
    delay(milliseconds); //During the delay the motors keep running till next line
  }
  
  stopp(); //stop and add angle to path
  delay(1000);
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

long US_high(){
  long duration, cm; //variable declaration for duration and distance (cm)
  
  digitalWrite(trigPin, LOW); //trigpin is being set on low, soundwave is about to be sent out
  delayMicroseconds(2); //small delay before soundwave is being send out
  digitalWrite(trigPin, HIGH); //soundwave is being sent out
  delayMicroseconds(5); //the soundwave is lasting for 5 microseconds
  digitalWrite(trigPin, LOW); //the trigpin is being turned off -> no soundwave is being sent out now
  
  duration = pulseIn(echoPin, HIGH); //when the soundwave is being returned, the echopin will detect this and this duration is being saved in the variable duration
  
  cm = microsecondsToCentimeters(duration); //the duration is being send to another function, for the distance to be calculated
  return cm; //this is the final distance that can be used in the main loop
}
long US_low(){
  long duration, cm;  //variable declaration for duration and distance (cm)

  pinMode(pingPin, OUTPUT); //pingpin is being set to output, so that it can send out a soundwave
  digitalWrite(pingPin, LOW); //pingpin is being set on low, soundwave is about to be sent out
  delayMicroseconds(2); //small delay before soundwave is being send out
  digitalWrite(pingPin, HIGH); //soundwave is being sent out
  delayMicroseconds(5); //the soundwave is lasting for 5 microseconds
  digitalWrite(pingPin, LOW); //the pingpin is being turned off -> no soundwave is being sent out now

  pinMode(pingPin, INPUT); //pingpin is being set to input, so that it can detect the soundwave en note the duration
  duration = pulseIn(pingPin, HIGH); //when the soundwave is being returned, the pingpin set on the input will detect this and this duration is being saved in the variable duration 

  cm = microsecondsToCentimeters(duration); //the duration is being send to another function, for the distance to be calculated
  return cm; //this is the final distance that can be used in the main loop
}
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2; //function that changes the duration into a distance
}

int detect_mountain(){
   long US_High, US_Low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_Low = US_low(); //return distance from low ultrasound sensor
    US_High = US_high(); //return distance from high ultrasound sensor
    
    if(US_Low < (US_High+error_margin) && US_Low > (US_High-error_margin) && US_Low < max_distance && US_High < max_distance){ //if mountain is detected
      USservo.write(90);
      return angle; //return angle of rock sample
    }
    USservo.write(90);
  }
  return -1; //return -1 if no mountain
}

void mountain_function(int angle){
  drive_to_mountain(angle);
  drive_past_mountain();
}

void drive_to_mountain(int angle){
  
  long old_US_High; //declararion of older value US sensor
  long old_US_Low;
  long US_High;
  long US_Low;
  int IR_1;
  int IR_2;
  
  turn(angle); // turn robot towards the mountain
  USservo.write(90); // turn servo straight ahead towards mountain
  forward();
  
  IR_1 = IR1();
  IR_2 = IR2();

  old_US_Low = US_low();
  old_US_High = US_high();

  US_Low = US_low();
  US_High = US_high();
  
  while(old_US_High >= US_High && old_US_Low >= US_Low && US_High >= distance_to_mountain && US_Low >= distance_to_mountain && IR_1 != 1 && IR_2 !=1){ // while the distance does not increase and the distance to the mountainis not to close drive forwards
    
    old_US_Low = US_low();
    old_US_High = US_high();
    
    delay(update_interval);
    
    US_Low = US_low();
    US_High = US_high();
    
    IR_1 = IR1();
    IR_2 = IR2();
  }

  if(old_US_High <= US_High && old_US_Low <= US_Low){ // if the older value of the US sensor is smaller than the new one it means it looks past the mountain and is on the wrong path.
    stopp(0, counter_right); // stopp and save distance travveled
    angle = detect_track(); // search turn angle to get back on track
    mountain_function(angle); // start again at the beginning
    return;
  }
  if(IR_1 == 1 || IR_2 ==1){
    avoid_crater();
    angle = detect_mountain();
    drive_to_mountain(angle);
  }
  stopp(0, counter_right); // distance is lower or equal to minimal distance to mountain so stop and save distance travelled
}


int detect_track(){
   long US_High, US_Low;
  
  for(int angle = 90-width; angle<=90+width; angle++){ // US servo turns in range of 2 times width to find mountain
    USservo.write(angle); //turn 1 degree
    
    US_Low = US_low(); //return distance from low ultrasound sensor
    US_High = US_high(); //return distance from high ultrasound sensor
    
    if(US_Low < (US_High+error_margin) && US_Low > (US_High-error_margin) && US_Low < max_distance && US_High < max_distance){ //if mountain is detected
      USservo.write(90);
      return angle; //return angle of rock sample
    }
    USservo.write(90);
  }
  return -1; //return -1 if no mountain
}

int turn_away(){
  long US_High, US_Low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_Low = US_low(); //return distance from low ultrasound sensor
    US_High = US_high(); //return distance from high ultrasound sensor
    
    if(US_Low > out_of_sight && US_High > out_of_sight){ //if mountain is not detected
      return angle; //return angle of rock sample
    }
  }
  return -1;
}

void drive_past_mountain(){ // function to drive parallel to the mountain till it is passed

long US_High;
long US_Low;

  angle = turn_away(); // find angle to drive parallel to mountain
  turn(angle);
  USservo.write(0); // turn US sensor towards moountain
  forward();
  US_Low = US_low();
  US_High = US_high();
  
  while(US_High <= out_of_sight+error_driving_parallel_to_mountain && US_Low <= out_of_sight+error_driving_parallel_to_mountain){ // drive till you passed the mountain
    
    delay(update_interval);
    
    US_Low = US_low();
    US_High = US_high();
  }
  stopp(0, counter_right);
}

