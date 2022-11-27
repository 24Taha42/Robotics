#include <kipr/wombat.h>
#include <stdlib.h>
#include <math.h>

// This may or may not move the set servo number (given by argument servoNum) to a set position (given by argument finalPos) at a slowing rate 
void servoUp(int servoNum, , int finalPos, int endTime){
  // find the starting position of the servo
  int startPos = get_servo_position(servoNum);
  // set the current position of the servo equal to the starting position
  int currentPos = startPos;
  // declare variable start time - the time when time = 0
  double startTime = 0;
  // set variable current time equal to the start time
  double currentTime = startTime;
  // declare variable time percent - the percent of time that has elapsed
  double timePercent;
  // decalre variable wait factor - how long it should take for the servo to move the amount its told to move
  int waitFactor;
  
  enable_servos();
  // while the position of the servo is less than the final position, run the code inside the loop
  while (currentPos < finalPos){
    // increment current time by 0.1 every time the loop is run (this number is totally arbitrary)
    currentTime += .1;
    // calculate what percent of the time has elapsed
    timePercent = (currentTime-startTime) / (endTime-startTime);
    // set the current position of the servo as a function of the percent of time that has elapsed and the end displacement
    currentPos = (timePercent*(finalPos-startPos)) + startPos;
    // increase the wait factor quadratically to attempt to make a concave down increasing function
    waitFactor = (currentTime*currentTime)*0.1;
    
    // set the given servo to the current position, calculated earlier
    set_servo_position(servoNum,currentPos);
    // wait for the amount of seconds calculated earlier
    msleep(waitFactor);
  
  disable_servos();
}

int main(){
  
  // Tell servo 0 to go to position 1400 in 5 time units
  servoUp(0,1400,5);
  
  return 0;
}
