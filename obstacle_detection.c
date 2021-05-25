#include <Servo.h>
Servo USservo;
#define servoPin 11
#define error_margin 2
#define max_distance = 300

void setup_USservo() {
  USservo.attach(servoPin);
}

int detect_sample(int angle){
  long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high-error_margin) && US_low < max_distance){ //if rock sample is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no rock sample 
}

int detect_mountain(int angle){
   long US_high, US_low;
  
  for(int angle = 0; angle<=180; angle++){
    USservo.write(angle); //turn 1 degree
    
    US_low = US_low(); //return distance from low ultrasound sensor
    US_high = US_high(); //return distance from high ultrasound sensor
    
    if(US_low < (US_high+error_margin) && US_low > (US_high-error_margin) && US_low < max_distance && US_high < max_distance){ //if mountain is detected
      return angle; //return angle of rock sample
    }
  }
  return -1; //return -1 if no mountain
}
