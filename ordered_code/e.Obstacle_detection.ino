int detect_sample(){
  long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance){ //if rock sample is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no rock sample 
}

int detect_mountain(){
   long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high+error_margin) && US_low > (US_high-error_margin) && US_low < max_distance && US_high < max_distance){ //if mountain is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no mountain
}

void drive_to_sample(int angle){

  long US_low;
  long old_US_low;
  int IR_1;
  int IR_2;
  
  IR_1 = IR_1();
  IR_2 = IR_2();

  turn(angle);
  USservo.write(90);

  old_US_low = US_low();
  US_low = US_low();
  
  forward();
  while(IR_1 != 1 && IR_2 !=1 && old_US_low >= US_low && US_low >= distance_to_sample){
    
    old_US_low = US_low();
    delay(update_interval);
    US_low = US_low();
  }
  if(old_US_low <= US_low){
    stopp(0, counter_right);
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
  stopp(0, counter_right);
}

int detect_track_crater(){
  long US_high, US_low;
  
  for(int angle = 90-widt; angle<=90+width; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance){ //if rock sample is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no rock sample 
}

void avoid_crater(){
  angle = 180;
  turn(180);
  forward();
  delay(1000); //for 10 cm
  stopp(0, counter_right);
  turn(-90);
  forward();
  delay(4000); //parallel to crater
  stopp(0, counter_right);
  turn(-90)
}
