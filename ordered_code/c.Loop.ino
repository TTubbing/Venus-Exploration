void loop(){
  angle = detect_sample();
  if(angle != -1){
    drive_to_sample(angle);
    return_sample();
  }
  else if(angle == -1){
    angle = detect_mountain();
    drive_to_mountain(angle);
  }
}
