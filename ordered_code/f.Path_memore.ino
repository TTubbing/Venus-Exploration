void reset_count(){ //reset distance count
  count_left = 0;
  count_right = 0;
}

void calculate_distance(){ //calculate distance travelled
  distance_left = (count_left/9)*Pi*diameter_wheel);
  distance_right = (count_right/9)*Pi*diameter_wheel);
}

//attach function to get rounds for left encoder
void isrLeft(){
  count_left++;
}

//attach function to get rounds for right encoder
void isrRight(){
  count_right++;
}

void addpath(int angle, int count){ //add path to path array
	  path[pathlength].angle = angle; //add angle
	  path[pathlength].count = count; //add distance
	  pathlength++; //increase length of path commands
	}
	
void initialise_path(){ //initialise all values in path array to 0
    for(int i = 0; int i < maxpath; i++){
        path[i].angle = 0;
        path[i].count = 0;
    }
}

void returnpath(){
    turn(180); //turn around
    
    for(int place = maxpath-1; place >= 0; place--){//loop backwards through path array
        forward(path[place].count);//drive forward amount in path array
        turn((path[place].angle)*-1);//drive opposite angle back
    }
}
