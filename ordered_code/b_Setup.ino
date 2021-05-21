void setup(){
  //setup communication
  Serial.begin(9600);
  xbee.begin(9600);
  
  //setup encoders
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
  
}
