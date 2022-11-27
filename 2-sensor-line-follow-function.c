#include <kipr/wombat.h>

left = 0;
right = 1;
white = 1600;

void followLine(){
  if (analog(left) < white && analog(right) < white){
    printf("I'm white");
  }
  else if (analog(left) > white && analog(right) < white){
    motor(0, -50);
    motor(1, 50);
  }
  else if (analog(left) < white && analog(right) > white){
    motor(0,50);
    motor(1,-50);
  }
  else if (analog(left) > white && analog(right) > white){
    motor(0,50);
    motor(1,50);
  }
  else{
    printf("what is happening?!");
  }
  
  int main(){
    
    followLine();
    
    return 0;
  }
