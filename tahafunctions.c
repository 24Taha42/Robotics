#include <kipr/wombat.h>
#include <stdio.h>

void easingservo(int servoNum, int finalPos, int endTime){
    int startPos = get_servo_position(servoNum);
    int currentPos = startPos;
    double startTime = seconds();
    double timePercent;
    //int waitFactor;

    enable_servos();
    while (abs(currentPos-startPos) < abs(finalPos-startPos)-5){
        timePercent = (seconds()-startTime) / (endTime);
        currentPos = (((timePercent*timePercent)*(3-(2*timePercent)))*(finalPos-startPos)) + startPos;
        //waitFactor = (seconds()*seconds())*0.01; 

        set_servo_position(servoNum,currentPos);
        msleep(1);
    }
    disable_servos();
}