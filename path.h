struct movement { //Structure that holds each movement command
  int angle; //angle of movement
  int distance; //distance of movement
};

int pathlength = 0; //length of path commands

struct movement path[20]; //path array

void addpath(int angle, int distance){ //add path to path array
  path[pathlength].angle = angle; //add angle
  path[pathlength].distance = distance; //add distance
  pathlength++; //increase length of path commands
}
