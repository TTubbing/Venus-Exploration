//include libraries
//communication
#include <SoftwareSerial.h>
//encoders
#include <EnableInterrupt.h>

//defining variables
#define encoderLeft = 7;
#define encoderRight = 8;

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
