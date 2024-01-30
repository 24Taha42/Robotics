#include <stdio.h>
#include <kipr/wombat.h>

void easingservo(int port, float finalpos, float secs){
  if (finalpos < 400 || finalpos > 1900){
    printf("You're going to far. Servo range = [400,1900]");
    return;
  }
  
  enable_servos();

  float initial = get_servo_position(port);
  float deltapos = finalpos-initial;
  float nowpos;
  const float starttime = seconds();
  float timepercent = (seconds()-starttime)/secs;
  
  while (timepercent <= 1){
      timepercent = (seconds()-starttime)/secs;
      nowpos = initial+(deltapos*((timepercent*timepercent)*(3-(2*timepercent))));
      set_servo_position(port,nowpos);
  }

  disable_servos();
}

int main()
{
  easingservo(0,400,2);
  return 0;
}

