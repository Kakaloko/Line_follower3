#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <stdlib.h>
#include "sensor.h"




void pico_button_init(void (*func)()){
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON,false);  
    gpio_pull_up(BUTTON);

    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, func);
}



void pico_sensor_init(){
    gpio_init(LL);
    gpio_set_dir(LL,false); 
    gpio_init(L);
    gpio_set_dir(L,false);
    gpio_init(RR);
    gpio_set_dir(RR,false);
    gpio_init(R);
    gpio_set_dir(R,false);
    gpio_init(MID);
    gpio_set_dir(MID,false);
}