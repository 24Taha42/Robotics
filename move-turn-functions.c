#include <kipr/wombat.h>
#include <stdlib.h>

int left = 0;
int right = 3;

void drive(int distance, int speed){
  cpmc(left);
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
  while (gmpc(countMotor) < distance){
    mav(left, leftSpeed);
    mav(right, rightSpeed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

int main(){  
  
  print("Hello World");
  
  return 0;
}
