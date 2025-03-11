#include <stdio.h>
#include "pico/stdlib.h"

#define LL 15
#define L 14
#define RR 13
#define R 12
#define M 11

void pico_output_init(); //TODO
void pico_sensors_init(); //TODO

int main()
{
    stdio_init_all();
    pico_sensor_init();
    
}




void pico_sensors_init(){
    gpio_init(SENSOR);
    gpio_set_pulls(15, false, true);
    gpio_set_dir(SENSOR, false);
}