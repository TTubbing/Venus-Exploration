void forward(){
  reset_count();
  if(robotNR == 1){
    LeftmotorServo.write(180+correction_left_drive); // Send signal to servo
    RightmotorServo.write(0+correction_right_drive); // 0 fast backwards, 90 stop, 180 fast forwards.
  }
  if(robotNR == 2){
    LeftmotorServo.write(0+correction_left_drive); // Left is 0 and right 180 because of the way installed
    RightmotorServo.write(180+correction_right_drive);
  }
}

void backward(){
  reset_count();
  if(robotNR == 1){
    LeftmotorServo.write(0+correction_left_drive); // Left is 0 and right 180 because of the way installed
    RightmotorServo.write(180+correction_right_drive);
  }
  if(robotNR == 2){
    LeftmotorServo.write(180+correction_left_drive); // Send signal to servo
    RightmotorServo.write(0+correction_right_drive); // 0 fast backwards, 90 stop, 180 fast forwards.
  }
}

void stopp(int angle, int count){
  LeftmotorServo.write(90+correction_left_stop); // Correction is needed to calibrate stop point
  RightmotorServo.write(90+correction_right_stop);
  addpath(angle, count); //Add angle and distance to path
  reset_count(); //Set encoder values to 0
}

void stoppp(){
  LeftmotorServo.write(90+correction_left_stop); // Correction is needed to calibrate stop point
  RightmotorServo.write(90+correction_right_stop);
}

void turn(int angle){
  
  int milli = 0;
  
  milli = abs(((float) angle/(float) 360)*timeturn); // seconds to turn the given angle
  Serial.print(milli);
  if(angle>0){ //turn right
    LeftmotorServo.write(180);
    RightmotorServo.write(180);
    delay(milli); // During the delay the motors keep running till next line
  }
  
  if(angle<0){ //turn left
    LeftmotorServo.write(0);
    RightmotorServo.write(0);
    delay(milli); //During the delay the motors keep running till next line
  }
  stopp(angle, 0); //stop and add angle to path
}
