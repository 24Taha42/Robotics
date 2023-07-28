// This file has many different types of squareup functions, using both touch and light sensors. They are ordered in increasing complexity

#include <kipr/wombat.h>
#include <stdlib.h>

// these variables make it easier for you to change ports and read your code. You can call them from the main file as well
int left = 0; // this allows you to assign a variable for the left motor's port number
int right = 3; // this allows you to assign a variable for the right motor's port number
int leftlight = 5; // this allows you to assign a variable for the left light (analog) sensor's port number. If you only have 1 light sensor, use this variable only
int rightlight = 4; // this allows you to assign a variable for the right light (analog) sensor's port number. This can also be used as a secondary variable
int lefttouch = 4; // this allows you to assign a variable for the left touch (digital) sensor's port number. If you only have 1 touch sensor, use this variable only
int righttouch = 1; // this allows you to assign a variable for the right touch (digital) sensor's port number. This can also be used as a secondary variable
int white = 700; // this is the maximum value that should be returned by your analog sensors when they see white. You may need to adjust this
int black = 3200; // this is the minimum value that should be returned by your analog sensors when they see black. You may need to adjust this
int drift_mod = 0; // this variable exists to offset any drift your robot has. This modification is applied to the left side, so if your robot is drifting right, it should be negative and if it is drifting left it should be positive

// Input any integer and it will return -1 if it is negative, 1 if it is positive, and 0 if it is 0
int sign(int x){
    if (x > 0) return 1; // if the input is positive, return 1
    else if (x < 0) return -1; // if the input is negative, return -1
    return 0;} // if the input is neither positive nor negative, return 0

// !!! Squaring up with one sensor is not advised, as you don't actually know if you're straight !!!

// Moves the robot until the specified touch sensor is pressed
// This function has 3 inputs: (1) the port number of the touch sensor which you are using to sense, 
// (2) the speed of the left motor (between -1500 & 1500), and (3) the speed of the right motor (between -1500 & 1500)
void driveDirect_until_touch(int port, int leftspeed, int rightspeed) {
    while (digital(port) == 0) { // while the specified touch sensor is NOT pressed, do the following:
        mav(left, leftspeed + drift_mod); // go forward with the left motor at a very high speed
        mav(right, rightspeed); // go forward with the right motor at a very high speed
    }
}

// Moves the robot until the specified light sensor sees black
// This function has 3 inputs: (1) the port number of the touch sensor which you are using to sense, (2) the speed of the left motor, and (3) the speed of the right motor
void driveDirect_until_light(int port, int leftspeed, int rightspeed) {
    while (analog(port) < black) { // while the specified light sensor does NOT see black, do the following:
        mav(left, leftspeed + drift_mod); mav(right, rightspeed); // go forward with the left & right motors at a very high speed
        // the line above is multiple lines smushed into one- yes, you can do that
    }
}

// Moves the robot to square up with a solid object
// !! only works if you have two working touch sensors
// This function has 1 input: the speed with which you want to arrive at the wall
// !! the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
void squareup_touch(int speed) {
    while (digital(lefttouch) == 0 || digital(righttouch) == 0) { // while either the left or right touch sensor is NOT pressed, do the following:
        if (digital(lefttouch) == 0) { mav(left, (speed)); } // if the left touch sensor is NOT pressed, move the left motor at full speed
        if (digital(righttouch) < black) { mav(right, (speed)); } // if the right touch sensor is NOT pressed, move the right motor at full speed
    }
}

// Moves the robot to square up with a black line
// !! only works if you have two working light sensors
// This function has 1 input: the speed with which you want to arrive at the black line
// !! the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
void squareup_light(int speed){
    while (analog(leftlight) < black || analog(rightlight) < black){ // while either the left or right light sensor does NOT see black, do the following:
        if (analog(leftlight) < black){ mav(left,(speed)); } // if the left light sensor does NOT see black, move the left motor at full speed 
        else { mav(left, (-1*(speed))*0.5); } // if the left light sensor does see black, move the left motor backward slowly
        if (analog(rightlight) < black){ mav(right,(speed)); } // if the right light sensor does NOT see black, move the right motor at full speed
        else { mav(right, (-1*(speed))*0.5); } // if the left light sensor does see black, move the left motor backward slowly
    }
}

// Moves the robot to square up with a solid object, but will stop trying after a certain number of seconds
// !! only works if you have two working touch sensors
// This function has 2 inputs: 
// 1. the speed with which you want to arrive at the wall- the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
// 2. the amount of time you want before the robot stops trying to square up in seconds (must be a positive whole number)
void protected_squareup_touch(int speed, int time) {
    float starttime = seconds(); // sets the start time equal to the number of seconds since the run began
    while ((digital(lefttouch) == 0 || digital(righttouch) == 0) && seconds()-starttime < time) { 
        // while either the left or right touch sensor is NOT pressed AND the amount of time specified hasn't elapsed, do the following:
        if (digital(lefttouch) == 0) { mav(left, (speed)); } // if the left touch sensor is NOT pressed, move the left motor at full speed
        if (digital(righttouch) == 0) { mav(right, (speed)); } // if the right touch sensor is NOT pressed, move the right motor at full speed
    }
}

// Moves the robot to square up with a black line, but will stop trying after a certain number of seconds
// !! only works if you have two working light sensors
// This function has 2 inputs: 
// 1. the speed with which you want to arrive at the wall- the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
// 2. the amount of time you want before the robot stops trying to square up in seconds (must be a positive whole number)
void protected_squareup_light(int speed, int time) {
    float starttime = seconds(); // sets the start time equal to the number of seconds since the run began
    while ((analog(leftlight) < black || analog(rightlight) < black) && seconds()-starttime < time) { 
        // while either the left or right light sensor does NOT see black AND the amount of time specified hasn't elapsed, do the following:
        if (analog(leftlight) < black) { mav(left, (speed)); } // if the left light sensor does NOT see black, move the left motor at full speed 
        else { mav(left, (-1 * (speed)) * 0.5); } // if the left light sensor does see black, move the left motor backward slowly
        if (analog(rightlight) < black) { mav(right, (speed)); } // if the right light sensor does NOT see black, move the right motor at full speed
        else { mav(right, (-1 * (speed)) * 0.5); } // if the right light sensor does see black, move the right motor backward slowly
    }
}

// Moves the robot to square up with a black line, but will turn left if it hasn't been able to find the line after a certain amount of time
// !! only works if you have two working light sensors
// This function has 2 inputs: 
// 1. the speed with which you want to arrive at the wall- the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
// 2. the amount of time you want before the robot turns left (in seconds- must be a positive whole number)
void autocorrect_left_squareup_light(int speed, int time) {
    int starttime = seconds(); // sets the start time equal to the number of seconds since the run began
    while (analog(leftlight) < black || analog(rightlight) < black) {
        // while either the left or right light sensor does NOT see black AND the amount of time specified hasn't elapsed, do the following:
        if (analog(leftlight) < black) { mav(left, (speed)); } // if the left light sensor does NOT see black, move the left motor at full speed 
        else { mav(left, (-1 * (speed)) * 0.5); } // if the left light sensor does see black, move the left motor backward slowly
        if (analog(rightlight) < black) { mav(right, (speed)); } // if the right light sensor does NOT see black, move the right motor at full speed
        else { mav(right, (-1 * (speed)) * 0.5); } // if the right light sensor does see black, move the right motor backward slowly
        if ((starttime - seconds) % time == 0) { turnLeft(476, 1204); }
        // whenever the number of seconds specified elpases, the robot will turn left slightly
        // !! This requires you to have the turnLeft() function in your code somewhere above
    }
}

// Moves the robot to square up with a black line, but will turn right if it hasn't been able to find the line after a certain amount of time
// !! only works if you have two working light sensors
// This function has 2 inputs: 
// 1. the speed with which you want to arrive at the wall- the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
// 2. the amount of time you want before the robot turns right (in seconds- must be a positive whole number)
void autocorrect_right_squareup_light(int speed, int time) {
    int starttime = seconds(); // sets the start time equal to the number of seconds since the run began
    while (analog(leftlight) < black || analog(rightlight) < black) {
        // while either the left or right light sensor does NOT see black AND the amount of time specified hasn't elapsed, do the following:
        if (analog(leftlight) < black) { mav(left, (speed)); } // if the left light sensor does NOT see black, move the left motor at full speed 
        else { mav(left, (-1 * (speed)) * 0.5); } // if the left light sensor does see black, move the left motor backward slowly
        if (analog(rightlight) < black) { mav(right, (speed)); } // if the right light sensor does NOT see black, move the right motor at full speed
        else { mav(right, (-1 * (speed)) * 0.5); } // if the right light sensor does see black, move the right motor backward slowly
        if ((starttime - seconds) % time == 0) { turnRight(476, 1204); }
        // whenever the number of seconds specified elpases, the robot will turn left slightly
        // !! This requires you to have the turnRight() function in your code somewhere above
    }
}