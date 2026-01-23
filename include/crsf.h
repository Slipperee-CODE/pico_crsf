#pragma once

#include "stdint.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define CRSF_SYNC_BYTE 0xC8
#define CRSF_MAX_PACKET_LEN 64

typedef struct __attribute((packed)){ //if you cast an address to a pointer to this type of struct, accessing struct_pointer->channel0 will access the next 11 bits starting at the address
    unsigned channel0 : 11;
    unsigned channel1 : 11;
    unsigned channel2 : 11;
    unsigned channel3 : 11;
    unsigned channel4 : 11;
    unsigned channel5 : 11;
    unsigned channel6 : 11;
    unsigned channel7 : 11;
    unsigned channel8 : 11;
    unsigned channel9 : 11;
    unsigned channel10 : 11;
    unsigned channel11 : 11;
    unsigned channel12 : 11;
    unsigned channel13 : 11;
    unsigned channel14 : 11;
    unsigned channel15 : 11;
    unsigned channel16 : 11;
} packed_payload_t;
 
void crsf_init(uart_inst_t* uart_port, uint8_t uart_tx, uint8_t uart_rx, void (*users_on_update_rc_channels_callback)(packed_payload_t*));

packed_payload_t* crsf_process_frame_internal(uint8_t* frame);

void crsf_read_incoming_frames();

void pico_crsf_is_library_accesible();