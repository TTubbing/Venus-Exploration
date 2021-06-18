void loop(){
  rockstate = sample_function();
  
  if(rockstate == 1){
    returnpath();
  }
  else{
   mountainstate = mountain_function();
  }
}
