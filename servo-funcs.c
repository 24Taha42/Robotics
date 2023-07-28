// This file has many different types of servo functions. They are ordered in increasing complexity

#include <kipr/wombat.h>
#include <stdlib.h>

// these variables make it easier for you to change ports and read your code. You can call them from the main file as well
int left = 0; // this allows you to assign a variable for the left motor's port number
int right = 3; // this allows you to assign a variable for the right motor's port number
int leftlight = 5; // this allows you to assign a variable for the left light (analog) sensor's port number. If you only have 1 light sensor, use this variable only
int rightlight = 4; // this allows you to assign a variable for the right light (analog) sensor's port number. This can also be used as a secondary variable
int leftTouch = 4; // this allows you to assign a variable for the left touch (digital) sensor's port number. If you only have 1 touch sensor, use this variable only
int rightTouch = 1; // this allows you to assign a variable for the right touch (digital) sensor's port number. This can also be used as a secondary variable
int white = 700; // this is the maximum value that should be returned by your analog sensors when they see white. You may need to adjust this
int black = 3200; // this is the minimum value that should be returned by your analog sensors when they see black. You may need to adjust this
int drift_mod = 0; // this variable exists to offset any drift your robot has. This modification is applied to the left side, so if your robot is drifting right, it should be negative and if it is drifting left it should be positive

// Input any integer and it will return -1 if it is negative, 1 if it is positive, and 0 if it is 0
int sign(int x){
    if (x > 0) return 1; // if the input is positive, return 1
    else if (x < 0) return -1; // if the input is negative, return -1
    return 0;} // if the input is neither positive nor negative, return 0

// Moves a servo slowly
// This function has 3 inputs:
// 1. The port # of the servo you are trying to move 
// 2. The final position which you are trying to move the servo to
// 3. The number of seconds you want the servo to take to move - must be an natural number (1,2,3,etc.)
void servo(int servoNum, int finalPos, int endTime){
    int startPos = get_servo_position(servoNum); // gets the starting position of the servo and assigns it to a new variable
    int currentPos = startPos; // sets the currents position of the servo equal to the start position
    double startTime = seconds(); // sets the current time equal to the number of seconds that have elapsed since the run began
    double timePercent; // creates a new variable called timePercent

    enable_servos(); // enables the servos so they can actually move
    while (abs(currentPos-finalPos) > 2){ // while the difference between the current and final position is greater than two, do the following:
        timePercent = (seconds()-startTime) / (endTime); // get the amount of time that has elapsed since this function was called and divide it by the total time the function should take
        currentPos = ((timePercent)*(finalPos-startPos)) + startPos; // calculate what position the servo should be at given the beginning position, the end position, and the time that has elapsed

        set_servo_position(servoNum,currentPos); // actually set the servo position equal to the calculated value
        msleep(1); // wait a millisecond (the minimum amount of time for it to work)
    }
    disable_servos(); // disable the servos
}

// Moves a servo slowly
// This function has 3 inputs:
// 1. The port # of the servo you are trying to move 
// 2. The final position which you are trying to move the servo to
// 3. The number of seconds you want the servo to take to move - must be an natural number (1,2,3,etc.)
void servo(int servoNum, int finalPos, int endTime) {
    if (finalPos <= 400 || finalPos >= 1900) { printf("Error: The final position inputed will damage the servo"); return; }
    // if the final position is less than/ equal to 400 or greater than/ equal to 1900, abort the function
   
    int startPos = get_servo_position(servoNum); // gets the starting position of the servo and assigns it to a new variable
    int currentPos = startPos; // sets the currents position of the servo equal to the start position
    double startTime = seconds(); // sets the current time equal to the number of seconds that have elapsed since the run began
    double timePercent; // creates a new variable called timePercent

    enable_servos(); // enables the servos so they can actually move
    while (abs(currentPos - finalPos) > 2) { // while the difference between the current and final position is greater than two, do the following:
        timePercent = (seconds() - startTime) / (endTime); // get the amount of time that has elapsed since this function was called and divide it by the total time the function should take
        currentPos = ((timePercent) * (finalPos - startPos)) + startPos; // calculate what position the servo should be at given the beginning position, the end position, and the time that has elapsed

        set_servo_position(servoNum, currentPos); // actually set the servo position equal to the calculated value
        msleep(1); // wait a millisecond (the minimum amount of time for it to work)
    }
    disable_servos(); // disable the servos
}

// Moves a servo slowly
// This function has 3 inputs:
// 1. The port # of the servo you are trying to move 
// 2. The final position which you are trying to move the servo to
// 3. The number of seconds you want the servo to take to move - must be an natural number (1,2,3,etc.)
void servo(int servoNum, int finalPos, int endTime) {
    if (finalPos <= 400 || finalPos >= 1900) { printf("Error: The final position inputed will damage the servo"); return; }
    // if the final position is less than/ equal to 400 or greater than/ equal to 1900, abort the function
    
    int startPos = get_servo_position(servoNum); // gets the starting position of the servo and assigns it to a new variable
    int currentPos = startPos; // sets the currents position of the servo equal to the start position
    double startTime = seconds(); // sets the current time equal to the number of seconds that have elapsed since the run began
    double timePercent; // creates a new variable called timePercent
    int waitFactor; // creates a new variable called waitFactor

    enable_servos(); // enables the servos so they can actually move
    while (abs(currentPos - finalPos) > 2) { // while the difference between the current and final position is greater than two, do the following:
        timePercent = (seconds() - startTime) / (endTime); // get the amount of time that has elapsed since this function was called and divide it by the total time the function should take
        currentPos = ((timePercent) * (finalPos - startPos)) + startPos; // calculate what position the servo should be at given the beginning position, the end position, and the time that has elapsed
        waitFactor = (seconds()*seconds())*0.01; // the longer the function has been running, the slower the servo moves to create a more gentle curve 

        set_servo_position(servoNum, currentPos); // actually set the servo position equal to the calculated value
        msleep(waitFactor); // wait a millisecond (the minimum amount of time for it to work)
    }
    disable_servos(); // disable the servos
}