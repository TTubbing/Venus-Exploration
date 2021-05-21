#define sensor 2
//int sensorPin = A2;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {

 Serial.begin(9600);
  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensor);

Serial.print(sensorValue);
Serial.print("\n");
delay(50);
}
