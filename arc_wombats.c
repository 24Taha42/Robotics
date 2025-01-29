#include <stdio.h>
#include <kipr/wombat.h>

float ticksPerInch = 270;
float wheelDist = 6;
int right = 0;
int left = 3;

void circle_clockwise(int radius){
  cmpc(right);
  float circum = 6.28318*radius*ticksPerInch;

  float power_right = 100/(1+(wheelDist/radius));
  while (gmpc(right) < circum){
    motor(left,100);
    motor(right,power_right);
  }
}

void circle_counter_clockwise(int radius){
  cmpc(left);
  float circum = 6.28318*radius*ticksPerInch;

  float power_left = 100/(1+(wheelDist/radius));
  while (gmpc(left) < circum){
    motor(left,power_left);
    motor(right,100);
  }
}

void arc_right(int radius, float degrees){
  cmpc(right);
  float arcLength = 6.28318*radius*ticksPerInch*(degrees/360);

  float power_right = 100/(1+(wheelDist/radius));
  while (gmpc(right) < arcLength){
    motor(left,100);
    motor(right,power_right);
  }
}

void arc_left(int radius, float degrees){
  cmpc(left);
  float arcLength = 6.28318*radius*ticksPerInch*(degrees/360);

  float power_left = 100/(1+(wheelDist/radius));
  while (gmpc(left) < arcLength){
    motor(left,power_left);
    motor(right,100);
  }
}


int main()
{
  arc_left(2, 180);
  return 0;
}
