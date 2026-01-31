#include <stdio.h>
#include "pico/stdlib.h"
#include "crsf.h"

#define CRSF_UART_PORT uart1
#define CRSF_UART_TX 8
#define CRSF_UART_RX 9

void on_update_rc_channels(packed_payload_t* channels){
    printf("The value of channel 0 is %d \n", channels->channel0);
    printf("The value of channel 1 is %d \n", channels->channel1);
    printf("The value of channel 2 is %d \n", channels->channel2);
    printf("The value of channel 3 is %d \n", channels->channel3);
    printf("The value of channel 4 is %d \n", channels->channel4);
    printf("The value of channel 5 is %d \n", channels->channel5);
    printf("The value of channel 6 is %d \n", channels->channel6);
    printf("The value of channel 7 is %d \n", channels->channel7);
    printf("The value of channel 8 is %d \n", channels->channel8);
    printf("The value of channel 9 is %d \n", channels->channel9);    
}

int main()
{
    stdio_init_all();

    crsf_init(CRSF_UART_PORT, CRSF_UART_TX, CRSF_UART_RX, on_update_rc_channels);
    
    while (true) {
        //printf("This loop prints the value of channel0 \n");
        //pico_crsf_is_library_accesible();
        crsf_read_incoming_frames();
    }
}