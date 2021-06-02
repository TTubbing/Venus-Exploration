long IR_sensor(){
  sensorValue = analogRead(sensor);

Serial.print(sensorValue);
Serial.print("\n");
delay(50);

if (sensorValue > 550) { //the threshold value may differ...
  return 1;
else {
  return 0;
}
}
