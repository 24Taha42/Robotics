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

// Purpose: going straight forward or backward
// Moves the robot a specified amount {ticks} at a specified {speed} using move at velocity mav() function
void drive(int ticks, int speed){ // the first variable, ticks must always be positive. If you want to go backward, input speed as a negative value when calling the funciton
    cmpc(left); // clear the motor position counter for the left motor
    while (abs(gmpc(left)) < ticks){  // while the left motor has not moved the number of ticks specified when calling the funciton, do the following:
        mav(left, speed+drift_mod); // move the left motor at a speed specified when calling the function (between -1500 & 1500)
        mav(right, speed); // move the right motor at a speed specified when calling the function (between -1500 & 1500)
    }
    mav(left,0); mav(right,0); msleep(15); // pause for 15 milliseconds to resist the robot's inertia
}

// Purpose: turning left
// Turns the robot left a specified amount {ticks} at a specified {speed} 
void turnLeft(int ticks, int speed){ // the first variable is related to how long you want the turn to be and the second how sharp you want it to be
    if (sign(speed) < 0){ right = 0; left = 9; } // This fancy math allows you to go backward and left, which is similar to turning right 
    cmpc(right); // clear the motor position counter for the right motor
    while (abs(gmpc(right)) < ticks){ // while the right motor has not moved the number of ticks specified when calling the funciton, do the following:
        mav(left, -speed); // move the left motor backward at the negative value of the speed specified when calling the funtion (between -1500 & 0)
        mav(right, speed); // move the right motor at the speed specified when calling the function (between 0 & 1500)
    }
    mav(left,0); mav(right,0); msleep(15); // pause for 15 milliseconds to resist the robot's inertia
    left = 0; right = 3; // reset motor numbers (has to do with the fancy math, you don't need to worry about this)
}

// Purpose: turning right
// Turns the robot right a specified amount {ticks} at a specified {speed} 
void turnRight(int ticks, int speed){ // the first variable is related to how long you want the turn to be and the second how sharp you want it to be
    if (sign(speed) < 0){ left = 3; right = 9; } // This fancy math allows you to go backward and left, which is similar to turning right
    cmpc(left); // clear the motor position counter for the left motor 
    while (abs(gmpc(left)) < ticks){ // while the left motor has not moved the number of ticks specified when calling the funciton, do the following:
        mav(left, speed); // move the left motor at the speed specified when calling the function (between 0 & 1500)
        mav(right, -speed); // move the right motor backward at the negative value of the speed specified when calling the funtion (between -1500 & 0)
    }
    mav(left,0); mav(right,0); msleep(15); // pause for 15 milliseconds to resist the robot's inertia
    left = 0; right = 3; // reset motor numbers (has to do with the fancy math, you don't need to worry about this)
}

// Purpose: curving to the left or right
// Inspired by the create dirveDirect() function, this takes a {distance}, speed of the left motor {leftSpeed}, speed of the right motor {rightSpeed}, and which motor is used for motor position counting
void driveDirect(int ticks, int leftSpeed, int rightSpeed, int countMotor){
    // the first variable, ticks, specifies how many ticks you want the robot to move
    // the second & third variables specify the speed you want the left and right motors to move at respectively
    // the fourth variable specifies the motor with which you want to count ticks (either left or right)
    cmpc(countMotor); // clear the motor position counter for the motor specified by the fourth input (countMotor)
    while (abs(gmpc(countMotor)) < ticks){ // while the motor specified by the fourth input (countMotor) has not moved the number of ticks specified when calling the funciton, do the following:
        mav(left, leftSpeed+drift_mod); // move the left motor at the speed specified when calling the function (between -1500 & 1500) (leftSpeed)
        mav(right, rightSpeed); // move the right motor at the speed specified when calling the function (between -1500 & 1500) (rightSpeed)
    }
    mav(left,0); mav(right,0); msleep(15); // pause for 15 milliseconds to resist the robot's inertia
}

// Purpose: following the black line
// This function has 1 input: the port number of the light sensor with which you are following the line. 
// You can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_1(int sensor_port) {
    // !! this function is meant to be used inside of a loop; it will only run the following code once if not called inside of a loop
    if (analog(sensor_port) < black) { // if the specified light sensor does not see black, do the following:
        mav(left, 1453 + drift_mod); // go forward with the left motor at a very high speed
        mav(right, 960); // go forward with the right motor at a slower speed
        // combined, this means that the robot is going forward while turning to the right
    }
    else if (analog(sensor_port) >= black) { // if the light sensor does see black, do the following:
        mav(left, 960 + drift_mod); // go forward with the left motor at a slower speed
        mav(right, 1453); // go forward with the right motor at a very high speed
        // combined, this means that the robot is going forward while turning to the left
    }
}

// Purpose: two-sensor black line squareup
// Moves the robot forward at a specified {speed}, turning so that the robot is perpendicular to the black line
// !! only works if you have two working light sensors
void squareup(int speed){
    // !! the larger the absolute value of speed (can be between -1500 & 1500), the less percise the square up will be
    while (analog(leftlight) < black || analog(rightlight) < black){ // while either the left or right light sensor does not see black, do the following:
        if (analog(leftlight) < black){ mav(left,(speed)); } // if the left light sensor does not see black, move the left motor forward 
        else { mav(left, (-1*(speed))*0.5); } // if the left light sensor DOES see black, move the left motor backward slowly
        if (analog(rightlight) < black){ mav(right,(speed)); } // if the right light sensor does not see black, move the right motor forward
        else { mav(right, (-1*(speed))*0.5); } // if the left light sensor DOES see black, move the left motor backward slowly
    }
}

// Purpose: moving a servo slowly
// Moves a specified servo {servoNum} to a specified final position {finalPos} in a specified number of seconds (endTime}
void servo(int servoNum, int finalPos, int endTime){
    // the first variable specifes the port number of the servo you want to move, the second the position you want to move it to, and the last how many seconds you want it to take
    // !! endTime must be an natural number (1,2,3,etc.)
    int startPos = get_servo_position(servoNum); // gets the starting position of the servo and assigns it to a new variable
    int currentPos = startPos; // sets the currents position of the servo equal to the start position
    double startTime = seconds(); // sets the current time equal to the number of seconds that have elapsed since the run began
    double timePercent; // creates a new variable called timePercent
    //int waitFactor;

    enable_servos(); // enables the servos so they can actually move
    while (abs(currentPos-finalPos) > 2){ // while the difference between the current and final position is greater than two, do the following:
        timePercent = (seconds()-startTime) / (endTime); // get the amount of time that has elapsed since this function was called and divide it by the total time the function should take
        currentPos = ((timePercent)*(finalPos-startPos)) + startPos; // calculate what position the servo should be at given the beginning position, the end position, and the time that has elapsed
        //waitFactor = (seconds()*seconds())*0.01; 

        set_servo_position(servoNum,currentPos); // actually set the servo position equal to the calculated value
        msleep(1); // wait a millisecond (the minimum amount of time for it to work)
    }
    disable_servos(); // disable the servos
}
