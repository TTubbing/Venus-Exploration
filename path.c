struct movement { //Structure that holds each movement command
  int angle; //angle of movement
  int count; //distance of movement
};

int pathlength = 0; //length of path commands

struct movement path[20]; //path array

void addpath(int angle, int count){ //add path to path array
  path[pathlength].angle = angle; //add angle
  path[pathlength].count = count; //add distance
  pathlength++; //increase length of path commands
}

void returnpath(){
  for(
}
