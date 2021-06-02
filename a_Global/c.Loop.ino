void loop(){
  stoppp();
  int angle = detect_mountain();
  Serial.print(angle);
  Serial.print("\n");
  mountain_function(angle);
  delay(2000);
}
