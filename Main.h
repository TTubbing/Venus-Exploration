int IR = 1; //infrared detectable obstacles
int US_high, US_low = 0; //distance to obstacle
int mountain, cliff, rock = 0;
int min_distance = 15; //Minimum distance to an obstacle
int IR_forward = 10; //distance to drive after detecting black tape
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
    distance_left = 0; //set distance count to 0
    distance_right = 0; //set distance count to 0
    
    while(distance_right < IR_forward && distance_left < IR_forward){
      calculate_distance();
    }
    stopp();
    
    IR = ir_input(); //read infrared input again
    
    if(IR == 0){ //black tape again -> it is a cliff
      cliff = 1;
    }
    else{
      border = 1;
    }
}
