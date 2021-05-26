int update_interval = 300; // interval between measurements
int distance_to_mountain; // ditance to the mountain
int width = 10; // width of search area to find the montain again
int out_of_sight; // minimal distance till mountain is out of sight
int error_driving_parallel_to_mountain = 4;

void mountain_function(int angle){
  drive_to_mountain(angle);
  drive_past_mountain();
}

void drive_to_mountain(int angle){
  
  long old_US_high; //declararion of older value US sensor
  long old_US_low;
  long US_high;
  long US_low;
  int IR_1;
  int IR_2;
  
  turn(angle); // turn robot towards the mountain
  USservo.write(90); // turn servo straight ahead towards mountain
  forward();
  
  IR_1 = IR_1();
  IR_2 = IR_2();

  old_US_low = US_low();
  old_US_high = US_high();

  US_low = US_low();
  US_high = US_high();
  
  while(old_US_high >= US_high && old_US_low >= US_low && US_high >= distance_to_mountain && US_low >= distance_to_mountain && IR_1 ! = 1 && IR_2 !=1){ // while the distance does not increase and the distance to the mountainis not to close drive forwards
    
    old_US_low = US_low();
    old_US_high = US_high();
    
    delay(update_interval);
    
    US_low = US_low();
    US_high = US_high();
    
    IR_1 = IR_1();
    IR_2 = IR_2();
  }

  if(old_US_high <= US_high && old_US_low <= US_low){ // if the older value of the US sensor is smaller than the new one it means it looks past the mountain and is on the wrong path.
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
   long US_high, US_low;
  
  for(int angle = 90-width; angle<=90+width; angle++){ // US servo turns in range of 2 times width to find mountain
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high+error_margin) && US_low > (US_high-error_margin) && US_low < max_distance && US_high < max_distance){ //if mountain is detected
      USservo.write(90);
      return angle; //return angle of rock sample
    }
    USservo.write(90);
  }
  return -1; //return -1 if no mountain
}

int turn_away(){
  long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low > out_of_sight && US_high > out_of_sight){ //if mountain is not detected
      return angle; //return angle of rock sample
    }
  }
  return -1;
}

void drive_past_mountain(){ // function to drive parallel to the mountain till it is passed

long US_high;
long US_low;

  angle = turn_away(); // find angle to drive parallel to mountain
  turn(angle);
  USservo.write(0); // turn US sensor towards moountain
  forward();
  US_low = US_low();
  US_high = US_high();
  
  while(US_high <= out_of_sight+error_driving_parallel_to_mountain && US_low <= out_of_sight+error_driving_parallel_to_mountain){ // drive till you passed the mountain
    
    delay(update_interval);
    
    US_low = US_low();
    US_high = US_high();
  }
  stopp(0, counter_right);
}
