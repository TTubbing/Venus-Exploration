int encoderLeft = 7;
int encoderRight = 8;
int count_left, rounds_left = 0;
int count_right, rounds_right = 0;
float diameter_wheel = 0;
float distance_left, distance_right = 0;

void setup_decoders(){
  pinMode(encoderLeft, INPUT);
  pinMode(encoderRight, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderLeft), isrLeft ,RISING); //attach function for left encoder
  attachInterrupt(digitalPinToInterrupt(encoderRight), isrRight ,RISING); //attach function for right encoder
  
}

void calculate_distance(){
  distance_left = rounds_left*PI*diameter_wheel; //calculate distance travelled by left wheel
  distance_right = rounds_right*PI*diameter_wheel; // calculate distance travelles by right wheel
}

//attach function to get rounds for left encoder
void isrLeft(){
  count_left++; //increase count per high signal
  if(count_left == 9){ //if count is 9 made full circle
    rounds_left++;
    count_left = 0;
  }
}

//attach function to get rounds for right encoder
void isrRight(){
  count_right++; //increase count per high signal
  if(count_right == 9){//if count is 9 made full circle
    rounds_right++;
    count_right=0;
  }
}
