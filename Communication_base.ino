#include <SoftwareSerial.h>
SoftwareSerial xbee(0, 1); // RX, TX
 int state;
 boolean at_lab_other_robot = false;
 boolean rock_found_other_robot = false;
 boolean at_lab = false;
 boolean rock_found = false;
 int nr_not_at_lab = 0;
 int nr_at_lab = 1;
 int nr_no_rock_found = 2;
 int nr_rock_found = 3;


void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
}

void loop() {
 receive_data();
  //Hey I'm from IR and we found a rock, now we have to send that to movement and to comms
  send_data(nr_rock_found);
}

void send_data(int data){
  Serial.print(data);
  xbee.print(data);
 switch(data){
  case 0:
          at_lab = false;
    break;
    case 1:
          at_lab = true;
    break;
    case 2:
          rock_found = false;
    break;
    case 3:
          rock_found = true;
    break;
}
}

void receive_data(){
  if(xbee.available() > 0){
    state = xbee.read();   
  }
  
  if(Serial.available() > 0){
      state = Serial.read();
  }
  switch(state){
    case 0:
          at_lab_other_robot = false;
    break;
    case 1:
          at_lab_other_robot = true;
    break;
    case 2:
          rock_found_other_robot = false;
    break;
    case 3:
          rock_found_other_robot = true;
    break;
    
  }
}
