int getInfraredValue(int pin){
  return analogRead(pin);
}

void driveRampUp(){
  int startInfraredValue = getInfraredValue(pinInfraredLeft);
  while((getInfraredValue(pinInfraredLeft) - startInfraredValue) < 50){
    forward();
  }
  stoppp();
  pickup();
}

void driveRampDown(){
  int startInfraredValue = getInfraredValue(pinInfraredLeft);
  while((startInfraredValue - getInfraredValue(pinInfraredLeft)) < 50){
    backward();
  }
  stoppp();
}

void pickup(){
  GripperservoPin.write(0);
  delay(500);
  GripperservoPin.write(180);
  delay(500);
}

void drop_lab(){
  stoppp();
  delay(1000);
  pickup();
  driveRampUp();
  backward();
  delay(1000);
  driveRampDown();
  stoppp();
  delay(500);
}

