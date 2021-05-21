typedef struct movement { //Structure that holds each movement command
  int angle; //angle of movement
  int count; //distance of movement
}movement;

const int maxpath = 20;
int pathlength = 0;
movement path[maxpath]; //path array

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
