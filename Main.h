int IR = 1; //infrared detectable obstacles
int US_high, US_low = 0; //distance to obstacle
int mountain, cliff, rock = 0;
int min_distance = 15; //Minimum distance to an obstacle
int lab = 1; //Robot at lab
int starting_sequence = 1;

void setup() {
  
}

void loop() {
  forward(); //drive forward
  
  IR = ir_input() //read infrared input
  US_high = US_high_input() //read input from high ultrasound sensor
  US_low = US_low_input() //read input from low ultrasound sensor
  
  if(US_low <= min_distance){ //if distance to obstacle is minimum
    if(US_high <= min_distance){ //check if high ultrasound sensor is same
      mountain = 1; //then mountain
    }
    else{
      rock = 1; //else rock
    }
  }
  
  if(IR == 0){
    
  }
}
