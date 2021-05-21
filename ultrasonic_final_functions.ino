#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

const int pingPin = 9; //pingpin declaration (on input 9)
long distance4, distance3; //distances declaration, distance 4 is the distance from the object to the upper sensor and distance 3 is the distance from the object to the lower sensor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}

void loop() {
  distance3 = Distance3pin(); //distance 3 represents the distance from the object to the lower sensor !this order is fixed, 3-pin must go first!
  distance4 = Distance4pin(); //distance 4 represents the distance from the object to the upper sensor
  
  Serial.println("distance 4pin "); //serial monitor display -> just for now
  Serial.println(distance4);
  Serial.println(" distance 3pin "); //serial monitor display -> just for now
  Serial.println(distance3);
}
long US_high(){
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
long US_low(){
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
