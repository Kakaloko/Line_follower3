#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "robot.h"
#include "engine.h"
#include "sensor.h"

#include "pico/cyw43_arch.h"
#include "lwip/udp.h"
#include "lwip/pbuf.h" 


#define Right_forward 20
#define Right_backward 19
#define Right_speed 21
#define Left_foward 18
#define Left_backward 17
#define Left_speed 22

#define WIFI_SSID "1003_2.4"
#define WIFI_PASSWORD "Szymek1999"
#define PORT 2137
#define ON_OFF_BUTTON 'p'

//global zmienne

char last_input = 'l';
bool on = false;


void pico_start_stop();
void pico_connect_to_wifi(char* wifi_ssid, char* wifi_password);
void udp_receive_callback( 
    void* arg,              // User argument - udp_recv `arg` parameter
    struct udp_pcb* upcb,   // Receiving Protocol Control Block
    struct pbuf* p,         // Pointer to Datagram
    const ip_addr_t* addr,  // Address of sender
    u16_t port );           // Sender port 


int main(void)
{
    stdio_init_all();

    pico_button_init(pico_start_stop);
    pico_sensor_init();
    Robot robot;
    robot_init_engines(&robot, Left_foward, Left_backward, Left_speed, Right_forward, Right_backward, Right_speed);
    


    if (cyw43_arch_init()) 
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();



    pico_connect_to_wifi(WIFI_SSID,WIFI_PASSWORD);

    //udp rece
    struct udp_pcb* pcb = udp_new_ip_type(IPADDR_TYPE_V4);
    if(udp_bind(pcb,IP4_ADDR_ANY4, PORT) != ERR_OK)
    {
        udp_remove(pcb);
        printf("The specified ipaddr and port are already bound to by another UDP PCB.");
        return 1;
    }
    udp_recv(pcb, udp_receive_callback, NULL);



    float speed = 0;
    float turn = 0;
    while (1)
    {   
        if(on)
        {
         switch (last_input)
            {
            case 'w':
                speed = 0.5;
                break;
            case 's':
                speed = -0.5;
                break;
            case 'a':
                speed = 0.5;
                turn = -0.5;
                break;
            case 'd':
                speed = 0.5;
                turn = 0.5;
                break;
            case ' ':
                turn = 0;
                break;
            case 'e':
                speed = 0;
                break;
            default:
                break;
            }
        }
        else
        {
            speed = 0;
            turn = 0;
        }
        robot_set_turn(&robot, turn);
        robot_set_speed(&robot, speed);
        cyw43_arch_poll();
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




void pico_connect_to_wifi(char* wifi_ssid,char* wifi_password){
    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(wifi_ssid, wifi_password, CYW43_AUTH_WPA2_AES_PSK, 30000)) 
    {
        printf("failed to connect.\n");
        exit(1);
    } 
    else
    {
        printf("Connected.\n");
    }

}

void udp_receive_callback( void* arg,              // User argument - udp_recv `arg` parameter
    struct udp_pcb* upcb,   // Receiving Protocol Control Block
    struct pbuf* p,         // Pointer to Datagram
    const ip_addr_t* addr,  // Address of sender
    u16_t port )            // Sender port
{           
        
    if(p == NULL)
    {
        pbuf_free(p);
        return;
    }
    //unpacking receiver value to last input to use it in while(1) loop
    last_input = *(char*)p->payload;
    printf("i received %c\n", last_input);
    if(last_input == ON_OFF_BUTTON)
    {
        pico_start_stop();
    }
    // Must free receive pbuf before return
    pbuf_free(p);
    return;
}
