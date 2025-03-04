#include <stdio.h>
#include "pico/stdlib.h"
#define R_FORWARD 16
#define R_BACKWARD 17
#define R_POWER 18
#define L_FORWARD 19
#define L_BACKWARD 20
#define L_POWER 21
#define SENSOR 15

void pico_output_init(); //TODO
void pico_input_init(); //TODO

int main()
{
    stdio_init_all();
    pico_input_init();
    while(1){
        if(gpio_get(SENSOR)){
            printf("1");
        }
        else{
            printf("0");
        }
        sleep_ms(500);
    }
}




void pico_input_init(){
    gpio_init(SENSOR);
    gpio_set_pulls(15, false, true);
    gpio_set_dir(SENSOR, false);
}