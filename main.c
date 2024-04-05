#include <kipr/wombat.h>
#include <stdio.h>
#include <tahafunctions.h>

// start astronaut 5 cm away of the center of the pvc connector connecting to the flagpole and 1 cm right of the center of the pvc connector

 
int c = 1;

int arm = 1;
int armpos[4] = {1757, 1650, 1100, 360};
// {all the way down, starting position, mostly down, all the way up}

int claw = 2;
int clawpos[2] = {1066,500};
// {starting position, closed astronaut}

int main()
{
    wait_for_light(0);
    
    shut_down_in(115);
    
    // setup
    create3_connect();
    printf("starting up");
    easingservo(arm,armpos[1],1); // arm down mostly
    easingservo(claw,clawpos[0],1); // claw open
    
    // pause
    ao();
    msleep(500);
    
    // go forward
    create3_drive_straight(0.5,0.4);
    create3_wait();
    
    // move arm down
    easingservo(arm,armpos[0],1);

    // close around astronaut
	easingservo(claw,clawpos[1],2);
    
    // move arm up
    easingservo(arm,1699,1);
    
    //drive straight to get the first rock
    create3_drive_straight(0.35, 0.46);
    
    // turn a teeeeneee bit to the right so that the second rock gets in the left side of the claw
    //create3_rotate_degrees(-5, 5);
    
    //drive straight to get the second rock 
    create3_drive_straight(0.42, 0.46);
    
    //turn left and get the third rock as well as the rest into rock heap
    create3_drive_arc_degrees(0.2, 54, 0.05);
    create3_wait();
    
    easingservo(arm,armpos[3],2); // arm up
    
    // get the third rock into the rock heap
    create3_drive_straight(0.56, 0.46);
    create3_wait();
    
    printf("Rocks in!");
    
    //move backwards in preparation of the movement of poms
    create3_drive_straight(-0.96,0.46);
    create3_wait();
    
    // turn right parallel to the orange poms
    create3_rotate_degrees(-240, -60); 
    
    // go forward along black line
    create3_drive_straight(0.33,0.46);
    
    // turn left over platform
    create3_rotate_degrees(60,30);
    
    create3_wait();
    easingservo(arm,500,1); // arm down a little
    
    // turn to knock cubes off
    create3_rotate_degrees(-24,-5);
    
    create3_wait();
    easingservo(claw,1100,1); // open claw to drop astronaut
    
    // raise arm to avoid hitting anything
    create3_wait();
    easingservo(arm,armpos[3],1);
    
    // turn left to grab cube
    create3_rotate_degrees(18,60);
    
    create3_wait();
    easingservo(arm,armpos[3]+320,1); // lower arm so it can grab cube
    easingservo(claw,600,1); // grab cube
    easingservo(arm,armpos[3],1); // raise arm
    
    // turn right to move the poms back into area 4
    create3_rotate_degrees(-110,-60);
    
    //back up out of area 4
    create3_drive_straight(-0.2,0.46);
    
    // turn left toward rock
    create3_rotate_degrees(35,20);
    
    // go forward toward rock
    create3_drive_straight(0.25,0.46);
    
    // arc left to get the last rock
    create3_drive_arc_degrees(0.03, 60, 0.06);
    
    // go forward to make sure the last rock is actually in
    create3_drive_straight(0.1,0.46);
    
    // arc toward rock heap
    create3_drive_arc_degrees(0.04, 160, 0.2);
    
    // get the last rocks into the rock heap
    create3_drive_straight(0.53,0.46);
    
    create3_wait();
    easingservo(claw,1400,1); // open claw to drop red cube
    
    
    create3_wait();

	return 0;
}
