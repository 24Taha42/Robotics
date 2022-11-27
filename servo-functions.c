#include <kipr/wombat.h>
#include <stdlib.h>

// This may or may not move the set servo number (given by argument servoNum) to a set position (given by argument finalPos) at a changing rate (given as a function of argument speed) 
void moveServo(int servoNum, , int finalPos, int speed){
  int startPos = get_servo_position(servoNum);
  float currentPos = startPos;
  float time = 0;
  float timeEnd = finalPos/speed;
  int timePercent;
  enable_servos();
  
  while (abs(currentPos) < finalPos){
    time += speed;
    timePercent = ((time*100)/timeEnd);
    currentPos = (timePercent*(finalPos-startPos)) + startPos;
    set_servo_position(servoNum,currentPos);
    msleep(1 - (1 - timePercent) * (1 - timePercent);
  
  disable_servos();
}

int main(){
  
  return 0;
}
