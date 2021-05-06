int encoderLeft = 7;
int encoderRight = 8;
int count_left, rounds_left = 0;
int count_right, rounds_right = 0;
float diameter_wheel = 0;
float distance_left, distance_right = 0;

void setup(){
  attachInterrupt(digitalPinToInterrupt(encoderLeft), ,RISING); //attach function for left encoder
  attachInterrupt(digitalPinToInterrupt(encoderRight), ,RISING); //attach function for right encoder
  
}

void loop(){
  distance_left = rounds_left*PI*diameter_wheel; //calculate distance travelled by left wheel
  distance_right = rounds_right*PI*diameter_wheel; // calculate distance travelles by right wheel
}

//get rounds for left encoder
void isrLeft(){
  count_left++;
  if(count_left == 9){
    rounds_left++;
    count_left = 0;
  }
}

//get rounds for right encoder
void isrRight(){
  count_right++;
  if(count_right == 9){
    rounds_right++;
    count_right=0;
  }
}
