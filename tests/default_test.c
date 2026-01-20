#include <stdio.h>
#include "pico/stdlib.h"
#include "crsf.h"

#define CRSF_UART_PORT uart1
#define CRSF_UART_TX 8
#define CRSF_UART_RX 9

void on_update_rc_channels(packed_payload_t* channels){
    printf("The value of channel 0 is %d", channels->channel0);
}

int main()
{
    stdio_init_all();

    crsf_init(CRSF_UART_PORT, CRSF_UART_TX, CRSF_UART_RX, on_update_rc_channels);
    
    while (true) {
        printf("This loop prints the value of channel0 \n");
        pico_crsf_is_library_accesible();
        crsf_read_incoming_frames();
    }
}