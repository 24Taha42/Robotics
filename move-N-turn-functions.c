#include <kipr/wombat.h>
// This library is included so that you can use the abs() function, which takes the absolute value of the argument
#include <stdlib.h>

// The left motor corresponds to port 0
int left = 0;
// The right motor correspons to port 1
int right = 3;

// This function moves the robot (theoretically) straight forward by applying a set amount of ticks/second (argument speed) for a set amount of ticks (argument distance) 
void drive(int distance, int speed){
  // clears the left motor's motor position counter
  cpmc(left);
  // as long as the number of ticks forward/backward that the left motor has moved is less than integer distance, the robot will run the code inside the while loop
  while (abs(gmpc(left)) < distance){
    // applies a set number of ticks/second (given by argument speed) to motors 0 and 1
    mav(left, speed);
    mav(right, speed);
  }
  // These lines are to stop the robot from drifting after it executes the previous lines
  mav(left,0);
  mav(right,0);
  msleep(15);
}

// The turnLeft() and turnRight() functions operate on the same principles that drive() does

// This function makes the robot left for a set amount of ticks (given by argument distance) at a set amount of ticks/second (given by argument speed)
void turnLeft(int distance, int speed){
  cmpc(right);
  while (gmpc(right) < distance){
    // applies a set number of ticks/second (given by argument speed multiplied by -1) to the left motor
    mav(left, -speed);
    // applies a set number of ticks/second (given by argument speed) to the right motor
    mav(right, speed);
  }
  mav(left,0);
  mav(right,0);
  msleep(15);
}

// This function is the same as the turnLeft() function, but with positive speed on the left motor and negative on the right
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

// inspired by the create's create_drive_direct() function, this moves the robot for a set amount of ticks (given by argument distance) with a set amount of ticks/second on the left and right motors respectively
// This function also takes the argument countMotor, which tells the function which motor's ticks to count
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
  // Call the functions inside of int main():
  
  // makes the robot turn the left motor forward and the right motor backward for 100 ticks, applying the ticks 50% of the seconds
  turnRight(100,750);
  
  // makes the robot turn both motors forward for 100 ticks, applying the ticks 50% of the seconds
  drive(100,750);
  
  // makes the robot turn the right motor forward and the left motor backward for 100 ticks, applying the ticks 50% of the seconds
  turnRight(100,750);
  
  // makes the robot go forward with a slight leftward angle for 100 ticks of the right motor
  driveDirect(100,600,750,3);
  
  return 0;
}
