//include libraries
//communication
#include <SoftwareSerial.h>
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
#define USservo 11
//global variables
//communication
int state;
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
int distance_for_gripper = 10;
int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors
Servo gripperservo;
//ultrasonic servo
Servo USservo
//basic movement
int timeturn = 2000; // Total time needed to turn 360 degree
int correction = -1; // Correction for the motors
Servo LeftmotorServo; // Define servos
Servo RightmotorServo;
//obstacle detection
const int error_margin = 2;
const int max_distance = 300;
int update_interval = 300; // interval between measurements
int distance_to_mountain; // ditance to the mountain
int width = 10; // width of search area to find the montain again
int out_of_sight; // minimal distance till mountain is out of sight
//path memory
typedef struct movement { //Structure that holds each movement command
  int angle; //angle of movement
  int count; //distance of movement
}movement;

const int maxpath = 20;
int pathlength = 0;
movement path[maxpath]; //path array

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
void turn(int angle);
//obstacle detection
void mountain_function(int angle);
void drive_to_mountain(int angle);
void drive_past_mountain();
int detect_track();
int turn_away();
int detect_sample();
int detect_mountain();
//path memory
void addpath(int angle, int count);
void initialise_path();
void returnpath();
