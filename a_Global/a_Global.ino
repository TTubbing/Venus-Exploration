//include libraries
//communication
//#include <SoftwareSerial.h>
//encoders
#include <EnableInterrupt.h>
//servos
#include <Servo.h>

//defining variables
#define encoderLeft 7
#define encoderRight 8
#define GripperservoPin 10
#define motorLeft 12
#define motorRight 13
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define Usservopin 11
#define sensor1

//global variables
const int robotNR = 2;
//communication
int state;
//SoftwareSerial xbee(0,1);
//basic boolean operators to determine the state of each robot
boolean at_lab_other_robot = false;
boolean rock_found_other_robot = false;
boolean at_lab = false;
boolean rock_found = false;
//integer operators used to determine what information to send at each instant
int nr_not_at_lab = 0;
int nr_at_lab = 1;
int nr_no_rock_found = 2;
int nr_rock_found = 3;

//encoders
volatile int count_left = 0;
volatile int count_right = 0;
float diameter_wheel = 6.5;
float distance_left, distance_right = 0;
const float Pi = 3.14159;

//gripper servo
int distance_for_gripper= 10;
Servo gripperservo;

//ultrasonic servo
Servo Usservo;

//basic movement
const int timeturn = 2200; // Total time needed to turn 360 degree
int correction_left_stop = 0;// Correction for the motors
int correction_right_stop = 77;
int correction_left_drive = 30;// Correction for the motors when driving
int correction_right_drive = 0;
Servo LeftmotorServo; // Define servos
Servo RightmotorServo;

//obstacle detection
const int error_margin = 5;
const int max_distance = 100;
const int error_driving_parallel_to_mountain = 4;
int update_interval = 50; // interval between measurements
int distance_to_mountain = 14; // distance to the mountain
int width = 10; // width of search area to find the montain again
int out_of_sight = 17; // minimal distance till mountain is out of sight
int distance_to_sample = 10;

//path memory
typedef struct movement { //Structure that holds each movement command
  int angle; //angle of movement
  int count; //distance of movement
}movement;

const int maxpath = 50;
int pathlength = 0;
movement path[maxpath]; //path array

//ultrasound
const int pingPin = 9; //pingpin declaration (on input 9)
long distance4, distance3; //distances declaration, distance 4 is the distance from the object to the upper sensor and distance 3 is the distance from the object to the lower sensor

//declare functions
//communication
void send_data(int data);
void receive_data();
//encoders
void reset_count();
void calculate_distance();
void isrLeft();
void isrRight();
//gripper servo
void GripperOpen();
void GripperClose();
void pick_up_rock();
//ultrasonic servo
void ServoToFront();
void ServoToRight();
void ServoToLeft();
//basic movement
void forward();
void backward();
void stopp(int angle, int count);
void stoppp();
void turn(int angle);
//obstacle detection
void mountain_function();
void drive_to_mountain(int angle);
void drive_past_mountain();
void drive_around_mountain();
void not_detect_mountain();
int detect_track();
int turn_away();
int detect_sample();
int detect_mountain();
//path memory
void addpath(int angle, int count);
void initialise_path();
void returnpath();
//ultrasound
long US_high_sensor();
long US_low_sensor();
long microsecondsToCentimeters(long microseconds);
//IR sensor
int IR_1_sensor();
int IR_2_sensor();
