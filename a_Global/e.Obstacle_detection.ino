int sample_function(){ //function to drive and collect samples
  int angle = detect_sample();
  if(angle == -1){
    return 0;
  }
  else{
    drive_to_sample(angle);
    return 1;
  }
}

int detect_sample(){//function to detect sample and return angle
  long US_high, US_low;
  Usservo.write(0);
  delay(1000);
  int angle_right, angle_left;
  for(angle_right = 0; angle_right<=180; angle_right+=5){
    Usservo.write(angle_right); //turn 5 degree
    delay(100);
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance && US_low > distance_to_mountain){//if rock sample is detected
      Usservo.write(angle_right+=5);
      delay(500);
      US_low = US_low_sensor(); //return distance from low ultrasound sensor
      US_high = US_high_sensor(); //return distance from high ultrasound sensor
      if(US_low < (US_high-error_margin) && US_low < max_distance && US_low > distance_to_mountain){
        break;
      }
    }
  }
  
  Usservo.write(180);
  delay(1000);
  for(angle_left = 180; angle_left>=0; angle_left-=5){
    Usservo.write(angle_left); //turn 5 degree
    delay(100);
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance && US_low > distance_to_mountain && angle_left > angle_right){//if rock sample is detected
      Usservo.write(angle_left-=5);
      delay(500);
      US_low = US_low_sensor(); //return distance from low ultrasound sensor
      US_high = US_high_sensor(); //return distance from high ultrasound sensor
      if(US_low < (US_high-error_margin) && US_low < max_distance && US_low > distance_to_mountain && angle_left > angle_right){
        int angle = (angle_left+angle_right)/2;
        return -angle+90;
      }
    }
  }
  
  return -1; //return -1 if no rock sample 
}

void grab_sample(){//fucntion to grap the sample
  gripperservo.write(180);
  forward();
  delay(1800);
  stopp(0, count_left);
  gripperservo.write(0);  
}

void drive_to_sample(int angle){//function to drive to sample
   //declararion of older value US sensor
  int IR_1;
  int IR_2;
  long old_US_low;
  long US_low;
  
  turn(angle, 1); // turn robot towards the sample
  Usservo.write(90);
  delay(1000);
  
  IR_1 = IR_1_sensor();
  IR_2 = IR_2_sensor();

  old_US_low = US_low_sensor();
  US_low = old_US_low;

  forward();
  while((old_US_low >= US_low - error_margin) && (US_low >= distance_to_rock) && (IR_1 != 1) && (IR_2 != 1)){ // while the distance does not increase and the distance to the mountainis not to close drive forwards
    old_US_low = US_low_sensor();
    delay(update_interval);
    
    US_low = US_low_sensor();
    
    delay(update_interval);
    
    IR_1 = IR_1_sensor();
    IR_2 = IR_2_sensor();
  }
  
  if(US_low < distance_to_rock){
    stopp(0,count_left);
    int angle = detect_sample();
    turn(angle,1);
    grab_sample();
    return;
  }
  
  if(old_US_low <= US_low){ // if the older value of the US sensor is smaller than the new one it means it looks past the mountain and is on the wrong path.
    stopp(0, count_left); // stopp and save distance travveled
    angle = detect_sample(); // search turn angle to get back on track
    drive_to_sample(angle);
    return;
  }
  if(IR_1 == 1 || IR_2 ==1){
    angle = detect_sample();
    drive_to_sample(angle);
  }
  stopp(0, count_left); // distance is lower or equal to minimal distance to mountain so stop and save distance travelled
}

int detect_mountain(){
   long US_high, US_low;
   Usservo.write(0); //turn 1 degree
   delay(1000);
  for(int angle = 0; angle<=180; angle+=5){
    Usservo.write(angle); //turn 1 degree
    delay(50);
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if((US_low < (US_high+error_margin)) && (US_low > (US_high-error_margin)) && (US_low < max_distance) && (US_high < max_distance)){ //if mountain is detected
      if(angle>5){
        angle += 15;
      }
      return (-angle+90); //return angle of rock sample
    }
  }
  return -1; //return -1 if no mountain
}

int IR_1_sensor(){
  return 0;
}

int IR_2_sensor(){
  return 0;
}

void drive_to_mountain(int angle){//function to drive to mountain
  
  long old_US_high; //declararion of older value US sensor
  long old_US_low;
  long US_high;
  long US_low;
  int IR_1;
  int IR_2;
  
  turn(angle,1); // turn robot towards the mountain
  Usservo.write(90);
  delay(1000);
  IR_1 = IR_1_sensor();
  IR_2 = IR_2_sensor();

  old_US_low = US_low_sensor();
  old_US_high = US_high_sensor();

  US_low = old_US_low;
  US_high = old_US_high;
  forward();
  
  while((old_US_high >= US_high - error_margin) && (US_high >= distance_to_mountain) && (IR_1 != 1) && (IR_2 != 1)){ // while the distance does not increase and the distance to the mountainis not to close drive forwards
    old_US_low = US_low_sensor();
    old_US_high = US_high_sensor();

    delay(update_interval);
    
    US_low = US_low_sensor();
    US_high = US_high_sensor();
    
    delay(update_interval);
    
    IR_1 = IR_1_sensor();
    IR_2 = IR_2_sensor();
  }

  if(old_US_high <= US_high && old_US_low <= US_low){ // if the older value of the US sensor is smaller than the new one it means it looks past the mountain and is on the wrong path.
    stopp(0, count_left); // stopp and save distance travveled
    angle = detect_mountain(); // search turn angle to get back on track
    drive_to_mountain(angle);
    return;
  }
  if(IR_1 == 1 || IR_2 ==1){
    angle = detect_mountain();
    drive_to_mountain(angle);
  }
  stopp(0, count_left); // distance is lower or equal to minimal distance to mountain so stop and save distance travelled
}


int detect_track(){
   long US_high, US_low;
  
  for(int angle = 90-width; angle<=90+width; angle++){ // US servo turns in range of 2 times width to find mountain
    Usservo.write(angle); //turn 1 degree
    
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high+error_margin) && US_low > (US_high-error_margin) && US_low < max_distance && US_high < max_distance){ //if mountain is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no mountain
}

int mountain_function(){//function to drive to and around mountain
  int angle = detect_mountain();
  if(angle == -1){
    return 0;
  }
  else{
    drive_to_mountain(angle);
    drive_around_mountain();
    return 1;
  } 
}

void drive_around_mountain(){//function to drive around mountain
  not_detect_mountain(); //look where mountain ends
  drive_past_mountain(); //drive past it
  turn(-90,1); //turn 90 degrees
  forward();
  delay(1000);
  drive_past_mountain(); //drive past it
}

void not_detect_mountain(){//function to find angle to turn away from mountain
  long US_high;
  long US_low;
  int angle = 90;
  
   for(angle = 90; angle>=0; angle-=5){
    Usservo.write(angle); //turn 5 degree
    delay(50);
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_high > distance_to_mountain + error_margin){ //if mountain is not detected
      if (angle>5){
        angle -= 60;
      }
       turn(-angle+90,1); //turn away
       break;
    }
} 
}

void drive_past_mountain(){ //function to drive parallel to the mountain till it is passed
  long US_high;
  long US_low;
  int angle = 90;

  Usservo.write(180); //turn servo to the left
  delay(1000);
  forward();
  US_high = 0;
  while(US_high <= distance_to_mountain + 10){ //While mountain is detected
    US_high = US_high_sensor();
    if(US_high<=distance_to_mountain){
      turn(1,1);
      forward();
    }
    delay(update_interval);
  }
  delay(800);
  stopp(0, count_left);
}
