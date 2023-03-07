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

// Input any integer and it will return -1 if it is negative, 1 if it is positive, and 0 if it is 0
int sign(int x){
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;}

// Written by chatGPT: takes a value between 0 and 1 and outputs another value between 0 & 1 using the cubic ease in out function (see easings.net/#easeInOutCubic)
double cubicEaseInOut(float t) {
	if (t < 0.5) {
		return 0.5 * t * t * t;
	}
	else {
		float f = 2 * t - 2;
		return 0.5 * (f * f * f + 2);
	}
}

// Moves the robot forward {distance} at {speed} using move at velocity mav() function
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

// Turns the robot left a certain amount {distance} at a certain {speed} 
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

// Turns the robot right a certain amount {distance} at a certain {speed} 
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

// Inspired by the create dirveDirect() function, this takes a {distance}, speed of the left motor {leftSpeed}, speed of the right motor {rightSpeed}, and which motor is used for motor position counting
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

// A function that is used for the follow the line function
void followLineBase(int prt, int spd){
    int error = analog(prt) - 3200;
    float speed_mod = error * 0.05;
    mav(left,spd-speed_mod);
    mav(right,spd+speed_mod);
}

// A function that is used for the follow the line function backward
void followLineBaseBack(int prt, int spd){
    int error = analog(prt) - 3200;
    float speed_mod = error * 0.05;
    mav(left, spd + speed_mod);
    mav(right, spd - speed_mod);
}

// This function has two types. The first type is to follow the line forward until the touch sensor (in digital port 0) is activated.
// The second is to follow the line for a given number of motor position counters (variable displacement).
void followLine(int type, int port, int speed, int displacement){
    if (type == 0){
        if (sign(speed) == 1){
            while (digital(0) == 0){
                followLineBase(port, speed); } } 
        else if (sign(speed) == -1){
            printf("going backward");
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
  double startTime = seconds();
  double timePercent;
  int waitFactor;
  
  enable_servos();
  while ((currentPos*up) < (finalPos*up)){
    timePercent = (seconds()-startTime) / (endTime-startTime);
    currentPos = (cubicEaseInOut(timePercent)*(finalPos-startPos)) + startPos;
    waitFactor = (seconds()*seconds())*0.01; 
        
    set_servo_position(servoNum,currentPos);
    msleep(waitFactor);
  }
  disable_servos();
}


int main()
{
    //set up in the backup storage so that left wheel is next to the black line and the back servo is against the pvc
    
    //wait_for_light(2);
    shut_down_in(118);
    
    // go forward a little
    drive(100,750);
    
    //turn left
    turnLeft(500,250);
    
    // turn right
    turnRight(400,200);
    
    //follow the line toward botgall until the touch sensor is pressed. 
    followLine(0, 4, -750, 0);
    
    return 0;
}
