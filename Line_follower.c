#include <stdio.h>

#include "pico/stdlib.h"
#include "robot.h"
#include "engine.h"

#define LL 15
#define L 14
#define RR 13
#define R 12
#define M 11


#define Right_forward 28
#define Right_backward 27
#define Right_speed 26
#define Left_foward 25
#define Left_backward 24
#define Left_speed 23

void pico_sensors_init();




int main(void)
{
    pico_sensors_init();
    Robot robot;
    robot_init_engines(&robot, Left_foward, Left_backward, Left_speed, Right_forward, Right_backward, Right_speed);
    int proportional = 0;   
    int error = 0 ;


    while (1)
    {
        robot_set_speed(&robot, 1)
        if(!gpio_get(M))
        {
            err
        }
    }
    
}





void pico_sensors_init(){
    gpio_init(LL);
    gpio_set_dir(LL,false);
    gpio_init(L);
    gpio_set_dir(L,false);
    gpio_init(RR);
    gpio_set_dir(RR,false);
    gpio_init(R);
    gpio_set_dir(R,false);
    gpio_init(M);
    gpio_set_dir(M,false);
}

