long US_high_sensor(){
  long duration, cm; //variable declaration for duration and distance (cm)
  
  digitalWrite(trigPin, LOW); //trigpin is being set on low, soundwave is about to be sent out
  delayMicroseconds(2); //small delay before soundwave is being send out
  digitalWrite(trigPin, HIGH); //soundwave is being sent out
  delayMicroseconds(5); //the soundwave is lasting for 5 microseconds
  digitalWrite(trigPin, LOW); //the trigpin is being turned off -> no soundwave is being sent out now
  
  duration = pulseIn(echoPin, HIGH); //when the soundwave is being returned, the echopin will detect this and this duration is being saved in the variable duration
  
  cm = microsecondsToCentimeters(duration); //the duration is being send to another function, for the distance to be calculated
  return cm; //this is the final distance that can be used in the main loop
}
long US_low_sensor(){
  long duration, cm;  //variable declaration for duration and distance (cm)

  pinMode(pingPin, OUTPUT); //pingpin is being set to output, so that it can send out a soundwave
  digitalWrite(pingPin, LOW); //pingpin is being set on low, soundwave is about to be sent out
  delayMicroseconds(2); //small delay before soundwave is being send out
  digitalWrite(pingPin, HIGH); //soundwave is being sent out
  delayMicroseconds(5); //the soundwave is lasting for 5 microseconds
  digitalWrite(pingPin, LOW); //the pingpin is being turned off -> no soundwave is being sent out now

  pinMode(pingPin, INPUT); //pingpin is being set to input, so that it can detect the soundwave en note the duration
  duration = pulseIn(pingPin, HIGH); //when the soundwave is being returned, the pingpin set on the input will detect this and this duration is being saved in the variable duration 

  cm = microsecondsToCentimeters(duration); //the duration is being send to another function, for the distance to be calculated
  return cm; //this is the final distance that can be used in the main loop
}
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2; //function that changes the duration into a distance
}
