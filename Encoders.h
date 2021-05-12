#include <EnableInterrupt.h>

int encoderLeft = 7;
int encoderRight = 8;
volatile int count_left, rounds_left = 0;
volatile int count_right, rounds_right = 0;
float diameter_wheel = 5;
float distance_left, distance_right = 0;

volatile uint16_t interruptCountLeft=0; // The count will go back to 0 after hitting 65535.
volatile uint16_t interruptCountRight=0; // The count will go back to 0 after hitting 65535.

void calculate_distance(){
  distance_left = rounds_left*PI*diameter_wheel; //calculate distance travelled by left wheel
  distance_right = rounds_right*PI*diameter_wheel; // calculate distance travelles by right wheel
}

//attach function to get rounds for left encoder
void isrLeft(){
  interruptCountLeft++;
}

//attach function to get rounds for right encoder
void isrRight(){
  interruptCountRight++;
}

void setup() {
  Serial.begin(115200);
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, CHANGE);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, CHANGE);
}

// In the loop we just display interruptCount. The value is updated by the interrupt routine.
void loop() {
  delay(1000);
  Serial.println(interruptCountLeft, DEC);
  Serial.println(interruptCountRight, DEC);
}
