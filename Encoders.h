#include <EnableInterrupt.h>

int encoderLeft = 7;
int encoderRight = 8;
volatile int count_left = 0;
volatile int count_right = 0;
float diameter_wheel = 6.5;
float distance_left, distance_right = 0;

void setup_encoders() {
  Serial.begin(115200);
  pinMode(encoderLeft, INPUT_PULLUP);
  enableInterrupt(encoderLeft, isrLeft, RISING);
  pinMode(encoderRight, INPUT_PULLUP);
  enableInterrupt(encoderRight, isrRight, RISING);
}

void reset_distance(){
  distance_left = 0;
  distance_right = 0;
}

void calculate_distance(){
  distance_left = (count_left/9)*PI*diameter_wheel; //calculate distance travelled by left wheel
  distance_right = (count_right/9)*PI*diameter_wheel; // calculate distance travelles by right wheel
}

//attach function to get rounds for left encoder
void isrLeft(){
  count_left++;
}

//attach function to get rounds for right encoder
void isrRight(){
  count_right++;
}
