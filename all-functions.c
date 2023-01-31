#include <kipr/wombat.h>
#include <stdlib.h>

// altered so that motors goes backward

int left = 0;
int right = 3;
int leftlight = 0;
int rightlight = 1;
int leftTouch = 0; 
int rightTouch = 1;
int white = 1600;

int sign(int x){
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;}

void drive(int distance, int speed){
  cmpc(left);
  while (abs(gmpc(left)) < distance){
    mav(left, speed);
    mav(right, speed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

void turnLeft(int distance, int speed){
  cmpc(right);
  while (gmpc(right) < distance){
    mav(left, -speed);
    mav(right, speed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

void turnRight(int distance, int speed){
  cmpc(left);
  while (gmpc(left) < distance){
    mav(left, speed);
    mav(right, -speed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

void driveDirect(int distance, int leftSpeed, int rightSpeed, int countMotor){
  cmpc(countMotor);
  while (abs(gmpc(countMotor)) < distance){
    mav(left, leftSpeed);
    mav(right, rightSpeed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

void followLineBase(int prt, int spd){
    int error = analog(prt) - 1700;
    float speed_mod = error * 0.07;
    mav(left,spd-speed_mod);
    mav(right,spd+speed_mod);
}

void followLineBaseBack(int prt, int spd){
    int error = analog(prt) - 1700;
    float speed_mod = error * 0.07;
    mav(left,spd-speed_mod);
    mav(right,spd+speed_mod);
}

void followLine(int type, int port, int speed, int displacement){
    if (type == 0){
        if (sign(speed) == 1){
            while (digital(0) == 0){
                followLineBase(port, speed); } } }
        else if (sign(speed) == -1){
            while (digital(0) == 0){
                followLineBaseBack(port, speed); } } }
    else if (type == 1){
        cmpc(left);
        if (sign(speed) == 1){
        	while (gmpc(left) < displacement){
        		followLineBase(port, speed); } } }
        else if (sign(speed) == -1){
            while (gmpc(left) > displacement){
        		followLineBaseBack(port, speed); } } }
}

/* In beta
void lineSquare(int speed){
	while (analog(leftlight) < white || analog(rightlight) < white){
      if (analog(leftlight) < white && analog(rightlight) < white){
        mav(left, speed);
        mav(right, speed);
      }
      else if (analog(leftlight) > white && analog(rightlight) < white){
        motor(left, -10);
        motor(right, 70);
      }
      else if (analog(leftlight) < white && analog(rightlight) > white){
        motor(left, 70);
        motor(right, -10);
      }
      else{
        printf("Que?!");
      }
    }
}
*/

void servo(int servoNum, int finalPos, int endTime, int up){
  int startPos = get_servo_position(servoNum);
  int currentPos = startPos;
  double startTime = 0;
  double currentTime = startTime;
  double timePercent;
  int waitFactor;
  
  enable_servos();
  while ((currentPos*up) < (finalPos*up)){
    currentTime += .1;
    timePercent = (currentTime-startTime) / (endTime-startTime);
    currentPos = (timePercent*(finalPos-startPos)) + startPos;
    waitFactor = (currentTime*currentTime)*0.1; 
        
    set_servo_position(servoNum,currentPos);
    msleep(waitFactor);
  }
  disable_servos();
}


int main()
{
    
    followLine(0, 1, -750, 10000);
    
    return 0;
}