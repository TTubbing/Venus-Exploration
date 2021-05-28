int detect_sample(){
  long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    Usservo.write(angle); //turn 1 degree
    
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance){ //if rock sample is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no rock sample 
}

int detect_mountain(){
   long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    Usservo.write(angle); //turn 1 degree
    
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high+error_margin) && US_low > (US_high-error_margin) && US_low < max_distance && US_high < max_distance){ //if mountain is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no mountain
}

/*void drive_to_sample(int angle){

  long US_low;
  long old_US_low;
  int IR_1;
  int IR_2;
  
  IR_1 = IR_1_sensor();
  IR_2 = IR_2_sensor();

  turn(angle);
  Usservo.write(90);

  old_US_low = US_low_sensor();
  US_low = US_low_sensor();
  
  forward();
  while(IR_1 != 1 && IR_2 !=1 && old_US_low >= US_low && US_low >= distance_to_sample){
    
    old_US_low = US_low_sensor();
    delay(update_interval);
    US_low = US_low_sensor();
  }
  if(old_US_low <= US_low){
    stopp(0, count_right);
    angle = detect_track_crater();
    drive_to_sample(angle);
    return;
  }
  if(IR_1 == 1 || IR_2 ==1){
  avoid_crater();
  angle = detect_sample();
  drive_to_sample(angle);
  return;
  }
  stopp(0, count_right);
}

int detect_track_crater(){
  long US_high, US_low;
  
  for(int angle = 90-widt; angle<=90+width; angle++){
    Usservo.write(angle); //turn 1 degree
    
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance){ //if rock sample is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no rock sample 
}
*/

void avoid_crater(){
  int angle = 180;
  turn(180);
  forward();
  delay(1000); //for 10 cm
  stopp(0, count_right);
  turn(-90);
  forward();
  delay(4000); //parallel to crater
  stopp(0, count_right);
  turn(-90);
}

void mountain_function(int angle){
  drive_to_mountain(angle);
  drive_past_mountain();
}

/*void drive_to_mountain(int angle){
  
  long old_US_high; //declararion of older value US sensor
  long old_US_low;
  long US_high;
  long US_low;
  int IR_1;
  int IR_2;
  
  turn(angle); // turn robot towards the mountain
  Usservo.write(90); // turn servo straight ahead towards mountain
  forward();
  
  IR_1 = IR_1_sensor();
  IR_2 = IR_2_sensor();

  old_US_low = US_low_sensor();
  old_US_high = US_high_sensor();

  US_low = US_low_sensor();
  US_high = US_high_sensor();
  
  while(old_US_high >= US_high && old_US_low >= US_low && US_high >= distance_to_mountain && US_low >= distance_to_mountain && IR_1 ! = 1 && IR_2 !=1){ // while the distance does not increase and the distance to the mountainis not to close drive forwards
    
    old_US_low = US_low_sensor();
    old_US_high = US_high_sensor();
    
    delay(update_interval);
    
    US_low = US_low_sensor();
    US_high = US_high_sensor();
    
    IR_1 = IR_1_sensor();
    IR_2 = IR_2_sensor();
  }

  if(old_US_high <= US_high && old_US_low <= US_low){ // if the older value of the US sensor is smaller than the new one it means it looks past the mountain and is on the wrong path.
    stopp(0, count_right); // stopp and save distance travveled
    angle = detect_track(); // search turn angle to get back on track
    mountain_function(angle); // start again at the beginning
    return;
  }
  if(IR_1 == 1 || IR_2 ==1){
    avoid_crater();
    angle = detect_mountain();
    drive_to_mountain(angle);
  }
  stopp(0, count_right); // distance is lower or equal to minimal distance to mountain so stop and save distance travelled
}*/


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

int turn_away(){
  long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    Usservo.write(angle); //turn 1 degree
    
    US_low = US_low_sensor(); //return distance from low ultrasound sensor
    US_high = US_high_sensor(); //return distance from high ultrasound sensor
    
    if(US_low > out_of_sight && US_high > out_of_sight){ //if mountain is not detected
      return angle; //return angle of rock sample
    }
  }
  return -1;
}

void drive_past_mountain(){ // function to drive parallel to the mountain till it is passed

long US_high;
long US_low;

  int angle = turn_away(); // find angle to drive parallel to mountain
  turn(angle);
  Usservo.write(0); // turn US sensor towards moountain
  forward();
  US_low = US_low_sensor();
  US_high = US_high_sensor();
  
  while(US_high <= out_of_sight+error_driving_parallel_to_mountain && US_low <= out_of_sight+error_driving_parallel_to_mountain){ // drive till you passed the mountain
    
    delay(update_interval);
    
    US_low = US_low_sensor();
    US_high = US_high_sensor();
  }
  stopp(0, count_right);
}
