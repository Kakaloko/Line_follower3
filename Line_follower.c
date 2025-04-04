#include <stdio.h>

#include "pico/stdlib.h"
#include "robot.h"
#include "engine.h"
#include "sensor.h"


#define Right_forward 20
#define Right_backward 19
#define Right_speed 21
#define Left_foward 18
#define Left_backward 17
#define Left_speed 22


bool on = false;

void pico_start_stop();


int main(void)
{
    pico_button_init(&pico_start_stop);
    pico_sensor_init();
    Robot robot;
    robot_init_engines(&robot, Left_foward, Left_backward, Left_speed, Right_forward, Right_backward, Right_speed);
    

    
    

    
    while (1)
    {   
        if(on)
        {
        robot_set_speed(&robot, 1);
        }
        else
        {
        robot_set_speed(&robot, 0);
        }
    }
    
}


void pico_start_stop(){
    if(on)
    {
        on = false;
        
    }else
    {
        on = true;
    }
}




