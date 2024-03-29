// This includes several functions, all of which can follow a black line. They are ordered by increasing complexity

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

// This function has no inputs. It assumes you are following the left side of the line with one port only, specifically the one associated with the variable leftlight
void follow_line_0() {
    while (1 == 1) { // the following code will run indefinetely, as one is always equal to one
        if (leftlight < black) { // if the light sensor does not see black, do the following:
            mav(left, 1453 + drift_mod); // go forward with the left motor at a very high speed
            mav(right, 960); // go forward with the right motor at a slower speed
            // combined, this means that the robot is going forward while turning to the right
        }
        else if (leftlight >= black) { // if the light sensor does see black, do the following:
            mav(left, 960 + drift_mod); // go forward with the left motor at a slower speed
            mav(right, 1453); // go forward with the right motor at a very high speed
            // combined, this means that the robot is going forward while turning to the left
        }
    }
}

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

// Follows the left side of the line forward
// This function has 1 input: the port number of the light sensor with which you are following the line. 
// You can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_until_touch(int port) {
    while (digital(lefttouch) == 0) { // while the left (primary) touch sensor is not pressed, do the following:
        follow_line_1(port); // We input the value of the port variable into this function when we call it
        // over here, a previous function is called within this one. All this means that we're running all the code inside of follow_line_1() instead of writing it all out again
    }
}

// Follows the left side of the line forward
// This function has 2 inputs: the port number of the light sensor with which you are following the line and the number of ticks you want the left wheel to move before ending the line follow
// For the port variable, you can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_until_ticks(int port, int ticks) {
    cmpc(left); // clear the left motor's position counter
    while (gmpc(left) < ticks) { // while the left motor has not moved the number of ticks specified, do the following:
        follow_line_1(port); // We input the value of the port variable into this function when we call it
    }
}

// Follows the left side of the line forward
// This function has 2 inputs: the port number of the light sensor with which you are following the line and the number of seconds you want to move before ending the line follow
// For the port variable, you can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_until_time(int port, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    while (seconds()-starttime < time) { // while the number of seconds specified has not elapsed, do the following:
        follow_line_1(port); // We input the value of the port variable into this function when we call it
    }
}

// Follows the left side of the line forward
// This function has 4 inputs: 
// 1. The port number of the light sensor with which you are following the line- you can input leftlight or rightlight (as you assigned them each a number) or a custom number
// 2. The port number of a touch sensor you want to use to tell if the robot is crashing into a wall- you can input lefttouch or righttouch (as you assigned them each a number) or a custom number
// 3. The number of ticks you want the left wheel to move before ending the line follow
// 4. The number of seconds you want to move before ending the line follow- must be a natural number (1,2,3,etc.)
void mega_line_follow_left(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && gmpc(left) < ticks && seconds() - starttime < time) { 
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        follow_line_1(port); // We input the value of the port variable into this function when we call it
    }
    // ^^ having so many checks can be useful to ensure you're robot doesn't go too far off course, but you'll rarely ever use all of the variables
}

// The same as the mega_line_follow_left() function, except it follows the right edge of the black line
// This is done by curving left when the sensor sees white, and right when the light sensor sees black instead of the opposite order which is used for following the left side
void mega_line_follow_right(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    cmpc(right); // clear the left motor's position counter
    while (digital(touchport) == 0 && gmpc(right) < ticks && seconds() - starttime < time) {
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        follow_line_1(port); // We input the value of the port variable into this function when we call it
    }
}

// This will follow the line forward until the sensor not being used to follow the line sees an intersecting black line
// This function has 1 input: direction. If you are following the left side of the line, input direction as 'l'. If you are following the right side, direction as 'r'
// !! use the single quotes around 'l' and 'r' when inputing them into the function
void follow_line_until_intersect(char direction) {
    if (direction == 'l') { // if 'l' is inputed as direction, do the following:
        while (analog(leftlight) < black) { follow_line_1(rightlight); }
        // while the left light sensor doesn't see black, follow the line forward with the right light sensor
        // above, multiple lines have been condensed into one for better readability
    }
    else if (direction == 'r') { // if 'l' is inputed as direction, do the following:
        while (analog(rightlight) < black) { follow_line_1(leftlight); }
        // while the right light sensor doesn't see black, follow the line forward with the left light sensor
    }
}

// Follows the line forward using TWO light sensors (woahhh)
// !! To use this, the two light sensors have to be spaced between 3 & 4 cm apart, so they can be on both sides of the black tape at the same time
// This function has 1 input: the number of ticks you want the left wheel to move before ending the line follow
void two_sensor_line_follow(int ticks) {
    cmpc(left); // clear the left motor's position counter
    while (gmpc(left) < ticks) { // while the left motor has not moved the number of ticks specified, do the following:
        if (analog(leftlight) < black) { mav(left, 1453 + drift_mod); } // if the left light sensor doesn't see black, full power to the left motor
        else if (analog(leftlight) >= black) { mav(left, 960 + drift_mod); } // if the left light sensor sees black, less power to the left motor
        if (analog(rightlight) < black) { mav(right, 1453); } // if the right light sensor doesn't see black, full power to the right motor
        else if (analog(rightlight) >= black) { mav(right, 960); } // if the right light sensor sees black, less power to the right motor
    }
}

// The same as the mega_line_follow_left() function, except it moves backward
void mega_line_follow_left_back(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the start time of the function equal to the number of seconds since the run began
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && abs(gmpc(left)) < ticks && seconds() - starttime < time) { // takes the absolute value of the left motor's position counter to avoid logic errors
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        if (analog(port) < black) { mav(left, -1453 - drift_mod); mav(right, -960); } // if the specified light sensor does not see black, go backward while curving to the left
        else if (analog(port) >= black) { mav(left, -960 - drift_mod); mav(right, -1453); } // if the specified light sensor does see black, go backward while curving to the right
    }
}

// The same as the mega_line_follow_left() function, except it moves backward and follows the right side of the black line
void mega_line_follow_right_back(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the start time of the function equal to the number of seconds since the run began
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && abs(gmpc(left)) < ticks && seconds() - starttime < time) { // takes the absolute value of the left motor's position counter to avoid logic errors
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        if (analog(port) < black) { mav(left, -960 - drift_mod); mav(right, -1453); } // if the specified light sensor does not see black, go backward while curving to the right
        else if (analog(port) >= black) { mav(left, -1453 - drift_mod); mav(right, -960); } // if the specified light sensor does see black, go backward while curving to the left
    }
}

// Follows the line forward using TWO light sensors (woahhh)
// To use this, the two light sensors have to be spaced between 3 & 4 cm apart, so they can be on both sides of the black tape at the same time
// This function has 4 inputs: 
// 1. The direction with which you want to follow the line (1 for foward, -1 for backward)
// 2. The port number of a touch sensor you want to use to tell if the robot is crashing into a wall- you can input lefttouch or righttouch (as you assigned them each a number) or a custom number
// 3. The number of ticks you want the left wheel to move before ending the line follow
// 4. The number of seconds you want to move before ending the line follow- must be a natural number (1,2,3,etc.)
void mega_two_sensor_line_follow(int direction, int ticks, int touchport, int time) {
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && abs(gmpc(left)) < ticks && seconds() - starttime < time) { 
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        if (analog(leftlight) < black) { mav(left, (1453 + drift_mod)*direction); } // if the left light sensor doesn't see black, full power to the left motor
        else if (analog(leftlight) >= black) { mav(left, (960 + drift_mod)*direction); } // if the left light sensor sees black, less power to the left motor
        if (analog(rightlight) < black) { mav(right, 1453*direction); } // if the right light sensor doesn't see black, full power to the right motor
        else if (analog(rightlight) >= black) { mav(right, 960*direction); } // if the right light sensor sees black, less power to the right motor
    }
}

// Follows the left line forward using a continous function rather than discrete, as we have been (the NerdHerd way)
// This function has 3 inputs: 
// 1. The port number of the light sensor with which you are following the line- you can input leftlight or rightlight (as you assigned them each a number) or a custom number
// 2. The speed with which you want to follow the line (between 0 & 1500)
// 3. The port number of a touch sensor you want to use to tell if the robot is crashing into a wall- you can input lefttouch or righttouch (as you assigned them each a number) or a custom number
void smooth_line_follow(int port, int speed, int touchport) {
    while (digital(touchport) == 0) { // while the specified touch sensor isn't pressed, do the following:
        int error = analog(port) - (black+white)*2/3; // determine the darkness that the light sensor sees- error is positively correlated with darkness
        float speed_mod = error * 0.03; // use the number from previous line to modify the speed of the the motors (the bigger the difference between the light sensor value and the desired value, the sharper the curve
        // the purpose of the coefficient of error is to dampen it's effect. You can change the coefficent if the robot is not making sharp enough turns
        mav(left, speed - speed_mod + drift_mod); // the darker it is, the less power to the left motor
        mav(right, speed + speed_mod); // the darker it is, the more power to the right motor
    }
}
