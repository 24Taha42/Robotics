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

// Input any integer and it will return -1 if it is negative, 1 if it is positive, and 0 if it is 0
int sign(int x){
    if (x > 0) return 1; // if the input is positive, return 1
    else if (x < 0) return -1; // if the input is negative, return -1
    return 0;} // if the input is neither positive nor negative, return 0

// This function has no inputs. It assumes you are following the left side of the line with one port only, specifically the one associated with the variable leftlight
void follow_line_1() {
    while (1 == 1) { // the following code will run indefinetely because one always equals one
        if (leftlight < black) { // if the light sensor does not see black, do the following:
            mav(left, 1453); // go forward with the left motor at a very high speed
            mav(right, 960); // go forward with the right motor at a slower speed
            // combined, this means that the robot is going forward while turning to the right
        }
        else if (leftlight >= black) { // if the light sensor does see black, do the following:
            mav(left, 960); // go forward with the left motor at a slower speed
            mav(right, 1453); // go forward with the right motor at a very high speed
            // combined, this means that the robot is going forward while turning to the left
        }
    }
}

// Follows the left side of the line forward
// This function has 1 input: the port number of the light sensor with which you are following the line. 
// You can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_2(int port) {
    while (digital(lefttouch) == 0) { // while the left (primary) touch sensor is not pressed, do the following:
        if (port < black) { // if the specified light sensor does not see black, do the following:
            mav(left, 1453); // go forward with the left motor at a very high speed
            mav(right, 960); // go forward with the right motor at a slower speed
            // combined, this means that the robot is going forward while turning to the right
        }
        else if (port >= black) { // if the specified light sensor does see black, do the following:
            mav(left, 960); // go forward with the left motor at a slower speed
            mav(right, 1453); // go forward with the right motor at a very high speed
            // combined, this means that the robot is going forward while turning to the left
        }
    }
}

// Follows the left side of the line forward
// This function has 2 inputs: the port number of the light sensor with which you are following the line and the number of ticks you want the left wheel to move before ending the line follow
// For the port variable, you can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_3(int port, int ticks) {
    cmpc(left); // clear the left motor's position counter
    while (gmpc(left) < ticks) { // while the left motor has not moved the number of ticks specified, do the following:
        if (port < black) { // if the specified light sensor does not see black, do the following:
            mav(left, 1453); // go forward with the left motor at a very high speed
            mav(right, 960); // go forward with the right motor at a slower speed
            // combined, this means that the robot is going forward while curving to the right
        }
        else if (port >= black) { // if the specified light sensor does see black, do the following:
            mav(left, 960); // go forward with the left motor at a slower speed
            mav(right, 1453); // go forward with the right motor at a very high speed
            // combined, this means that the robot is going forward while curving to the left
        }
    }
}

// Follows the left side of the line forward
// This function has 2 inputs: the port number of the light sensor with which you are following the line and the number of seconds you want to move before ending the line follow
// For the port variable, you can input leftlight or rightlight (as you assigned them each a number) or a custom number
void follow_line_4(int port, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    while (seconds()-starttime < time) { // while the number of seconds specified has not elapsed, do the following:
        if (port < black) { mav(left, 1453); mav(right, 960); } // if the specified light sensor does not see black, go forward while curving to the right
        else if (port >= black) { mav(left, 960); mav(right, 1453); } // if the specified light sensor does see black, go forward while curving to the left
        // the statements above are each multiple lines smushed into one- yes, you can do that
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
        if (port < black) { mav(left, 1453); mav(right, 960); } // if the specified light sensor does not see black, go forward while curving to the right
        else if (port >= black) { mav(left, 960); mav(right, 1453); } // if the specified light sensor does see black, go forward while curving to the left
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
        if (port < black) { mav(left, 960); mav(right, 1453); } // if the specified light sensor does not see black, go forward while curving to the left
        else if (port >= black) { mav(left, 1453); mav(right, 960); } // if the specified light sensor does see black, go forward while curving to the right
    }
}

// Follows the line forward using TWO light sensors (woahhh)
// To use this, the two light sensors have to be spaced between 3 & 4 cm apart, so they can be on both sides of the black tape at the same time
// This function has 1 input: the number of ticks you want the left wheel to move before ending the line follow
void two_sensor_line_follow(int ticks) {
    cmpc(left); // clear the left motor's position counter
    while (gmpc(left) < ticks) { // while the left motor has not moved the number of ticks specified, do the following:
        if (leftlight < black) { mav(left, 1453); } // if the left light sensor doesn't see black, full power to the left motor
        else if (leftlight >= black) { mav(left, 960); } // if the left light sensor sees black, less power to the left motor
        if (rightlight < black) { mav(right, 1453); } // if the right light sensor doesn't see black, full power to the right motor
        else if (rightlight >= black) { mav(right, 960); } // if the right light sensor sees black, less power to the right motor
    }
}

// The same as the mega_line_follow_left() function, except it moves backward
void mega_line_follow_left_back(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && abs(gmpc(left)) < ticks && seconds() - starttime < time) { // takes the absolute value of the left motor's position counter to avoid logic errors
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        if (port < black) { mav(left, -1453); mav(right, -960); } // if the specified light sensor does not see black, go backward while curving to the left
        else if (port >= black) { mav(left, -960); mav(right, -1453); } // if the specified light sensor does see black, go backward while curving to the right
    }
}

// The same as the mega_line_follow_left() function, except it moves backward and follows the right side of the black line
void mega_line_follow_right_back(int port, int touchport, int ticks, int time) {
    float starttime = seconds(); // sets the starttime of the function equal to the number of seconds since the run began
    cmpc(left); // clear the left motor's position counter
    while (digital(touchport) == 0 && abs(gmpc(left)) < ticks && seconds() - starttime < time) { // takes the absolute value of the left motor's position counter to avoid logic errors
        // while a) the touch sensor specified is not pressed, b) the left motor hasn't moved a specified number of ticks, AND c) the number of seconds specified has not elapsed, do the following:
        if (port < black) { mav(left, -960); mav(right, -1453); } // if the specified light sensor does not see black, go backward while curving to the right
        else if (port >= black) { mav(left, -1453); mav(right, -960); } // if the specified light sensor does see black, go backward while curving to the left
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
        if (leftlight < black) { mav(left, 1453*direction); } // if the left light sensor doesn't see black, full power to the left motor
        else if (leftlight >= black) { mav(left, 960*direction); } // if the left light sensor sees black, less power to the left motor
        if (rightlight < black) { mav(right, 1453*direction); } // if the right light sensor doesn't see black, full power to the right motor
        else if (rightlight >= black) { mav(right, 960*direction); } // if the right light sensor sees black, less power to the right motor
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
        mav(left, speed - speed_mod); // the darker it is, the less power to the left motor
        mav(right, speed + speed_mod); // the darker it is, the more power to the right motor
    }
}