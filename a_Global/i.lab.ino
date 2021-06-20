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

