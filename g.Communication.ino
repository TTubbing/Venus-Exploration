/*void send_data(int data){
  Serial.print(data);
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
}*/
