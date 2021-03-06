void setup(){
  //setup communication
  Serial.begin(9600);
  //xbee.begin(9600);
  
  //setup encoders
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
  
  //setup gripper servo
  gripperservo.attach(GripperservoPin);
  
  //setup movement
  LeftmotorServo.attach(motorLeft);
  RightmotorServo.attach(motorRight);
  
  //setup ultrasonic servo
  Usservo.attach(Usservopin);
  
  //setup ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  initialise_path();
}
