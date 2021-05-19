
#include <Servo.h>
Servo myservo;
#define servoPin 11

int object = 0;
int max_distance;
int margin;
int angle;
int IR;
int distance;
int length_gripper;
int distance_Right = 0;
int distance_Left =0;
int wait;
int step_length;

void setup() {
  myservo.attach(servoPin);
}

void loop() {

  for(int x = 0; x<=180; x++)
  {
    myservo.write(x);
    
    US_high = US_high_input(); //read input from high ultrasound sensor
    US_low = US_low_input(); //read input from low ultrasound sensor

    if(US_high<=US_low+margin && US_high>=US_low-margin){
      object = 1;
      distance = US_distance();
      angle = x-90;
      deliver_object(angle, distance);
    }

    
    if(US_high>=US_low && object != 1){
      object = 2;
    }
  }
}

void deliver_object(angle, distance){
  int distance_next = 0;

  if(angle>0){
    turnRight(angle);
    //save struct(angle, right distance, left distance, distance)
  }
  if(angle<0){
    turnLeft(angle);
    //save struct
  }

  forward();
  while(distance_next<distance-lenth_gripper){
    IR = ir_input;
  if(IR==1){
    stopp();
    // save struct (contains different distance only)
    turn_Right(90);
    // save struct (new angle)
    drive_crater_edge(distance_Right);
  }
}
}

void drive_crater_edge(distance_Right){
  distance = 0;
    
    forward();
    //distance_Right = function distance
    while(distance_Right_next<=step_length+distance_Right){
      //distance_Right_next = function distance
    }
    stopp();
    turn_left(90);
    // save distance_right = function distance and angle (save in struct)
    forward();
    IR = ir_input
    while(IR != 1 && distance_next <= step_length+distance){
      IR = ir_input;
      //distance_next = function distance
    }
    stopp();
    
    if(IR == 1){
      turn_right(180);
      forward();
      while(distance_next<=(2*distance)){//just distance because it is the distance from new point
        distance_next = distance;
      }
      stopp();
      distance = 0;
      drive_crater_edge(distance_Right);
    }
    //save in struct all data
    turn_left(90);
    IR = ir-input;
    while(turn_left_next<)
     
}
}
