void forward(){
  reset_count();
  if(robotNR == 1){
    LeftmotorServo.write(180); // Send signal to servo
    RightmotorServo.write(0); // 0 fast backwards, 90 stop, 180 fast forwards.
  }
  if(robotNR == 2){
    LeftmotorServo.write(0); // Left is 0 and right 180 because of the way installed
    RightmotorServo.write(180);
  }
}

void backward(){
  reset_count();
  if(robotNR == 1){
    LeftmotorServo.write(0); // Left is 0 and right 180 because of the way installed
    RightmotorServo.write(180);
  }
  if(robotNR == 2){
    LeftmotorServo.write(180); // Send signal to servo
    RightmotorServo.write(0); // 0 fast backwards, 90 stop, 180 fast forwards.
  }
}

void stopp(int angle, int count){
  LeftmotorServo.write(90+correction_left); // Correction is needed to calibrate stop point
  RightmotorServo.write(90+correction_right);
  addpath(angle, count); //Add angle and distance to path
  reset_count(); //Set encoder values to 0
}

void stoppp(){
  LeftmotorServo.write(90+correction_left); // Correction is needed to calibrate stop point
  RightmotorServo.write(90+correction_right);
}

void turn(int angle){
  
  int milliseconds;
  
  milliseconds = (angle/360)*timeturn; // seconds to turn the given angle
  
  if(angle>0){ //turn right
    LeftmotorServo.write(180);
    RightmotorServo.write(180);
    delay(milliseconds); // During the delay the motors keep running till next line
  }
  
  if(angle<0){ //turn left
    milliseconds = (angle/360)*timeturn;
    LeftmotorServo.write(0);
    RightmotorServo.write(0);
    delay(milliseconds); //During the delay the motors keep running till next line
  }
  reset_count();
  stopp(angle, 0); //stop and add angle to path
}
