#include <kipr/wombat.h>
#include <stdlib.h>

// backward = toward craney push push arm with reactangle at end

int left = 0;
int right = 3;
int leftlight = 5;
int rightlight = 4;
int leftTouch = 9; 
int rightTouch = 1;
int white = 1600;
int black = 3200;

// Input any integer and it will return -1 if it is negative, 1 if it is positive, and 0 if it is 0
int sign(int x){
    if (x > 0) return 1;
    else if (x < 0) return -1;
    return 0;}

// Moves the robot forward {ticks} at {speed} using move at velocity mav() function
void drive(int ticks, int speed){
    cmpc(left);
    while (abs(gmpc(left)) < ticks && digital(0) < 1){
        mav(left, speed);
        mav(right, speed);
    }
    mav(left,0); mav(right,0); msleep(15); // pause
}

// Turns the robot left a certain amount {ticks} at a certain {speed} 
void turnLeft(int ticks, int speed){
    if (sign(speed) < 0){ right = 0; left = 9; } // if you put in a negative speed, change the motor numbers because it works better that way
    cmpc(right);
    while (abs(gmpc(right)) < ticks){
        mav(left, -speed);
        mav(right, speed);
    }
    mav(left,0); mav(right,0); msleep(15); // pause
    left = 0; right = 3; // reset motor numbers
}

// Turns the robot right a certain amount {ticks} at a certain {speed} 
void turnRight(int ticks, int speed){
    if (sign(speed) < 0){ left = 3; right = 9; } // if you put in a negative speed, change the motor numbers because it works better that way
    cmpc(left);
    while (abs(gmpc(left)) < ticks){
        mav(left, speed);
        mav(right, -speed);
    }
    mav(left,0); mav(right,0); msleep(15); // pause
    left = 0; right = 3; // reset motors numbers
}

// Inspired by the create dirveDirect() function, this takes a {distance}, speed of the left motor {leftSpeed}, speed of the right motor {rightSpeed}, and which motor is used for motor position counting
void driveDirect(int distance, int leftSpeed, int rightSpeed, int countMotor){
    cmpc(countMotor);
    while (abs(gmpc(countMotor)) < distance){
        mav(left, leftSpeed);
        mav(right, rightSpeed);
    }
    mav(left,0); mav(right,0); msleep(15); // pause
}

// A function that is used for the follow the line function
void followLineBase(int prt, int spd){
    int error = analog(prt) - 3000; // determine how black the light sensor sees
    float speed_mod = error * 0.03; // use the number from previous line to modify the speed of the the motors (the whiter, the bigger the speed modification)
    mav(left,spd-speed_mod); // turn more left the whiter it is
    mav(right,spd+speed_mod); // turn more left the whiter it is
}

// A function that is used for the follow the line function backward
void followLineBaseBack(int prt, int spd){
    int error = analog(prt) - 3000;
    float speed_mod = error * 0.03;
    mav(left, spd - speed_mod);
    mav(right, spd + speed_mod);
}

// This function has two types. The first type is to follow the line forward until the touch sensor (in digital port 0) is activated.
// The second is to follow the line for a given number of motor position counters (variable displacement).
void followLine(int type, int port, int speed, int displacement){
    if (type == 0){
        if (sign(speed) == 1){
            while (digital(leftTouch) == 0){
                followLineBase(port, speed); } } 
        else if (sign(speed) == -1){
            while (digital(leftTouch) == 0){
                followLineBaseBack(port, speed); } } }
    else if (type == 1){
        cmpc(left);
        if (sign(speed) == 1){
            while (gmpc(left) < displacement){
                followLineBase(port, speed); } } }
    else if (sign(speed) == -1){
        while (gmpc(left) > displacement){
            followLineBaseBack(port, speed); } } }

// if you want to square up with a black line using two light sensors...
void squareup(int speed){
    while (analog(leftlight) < black || analog(rightlight) < black){
        if (analog(leftlight) < black){ mav(left,speed); } // left wheel forward if left light sees white 
        else { mav(left, (-1*speed)*0.5); } // left wheel backward if left light sees black
        if (analog(rightlight) < black){ mav(right,speed); } // right wheel forward if right light sees white
        else { mav(right, (-1*speed)*0.5); } // right wheel forward if right light sees black
    }
}

void servo(int servoNum, int finalPos, int endTime, int up){
    int startPos = get_servo_position(servoNum);
    int currentPos = startPos;
    double startTime = seconds();
    double timePercent;
    //int waitFactor;

    enable_servos();
    while ((currentPos*up) < (finalPos*up)){
        timePercent = (seconds()-startTime) / (endTime);
        currentPos = ((timePercent)*(finalPos-startPos)) + startPos;
        //waitFactor = (seconds()*seconds())*0.01; 

        set_servo_position(servoNum,currentPos);
        msleep(1);
    }
    disable_servos();
}
