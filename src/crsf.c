#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "crsf.h"

void (*on_update_rc_channels_callback)(packed_payload_t*);
uart_inst_t* UART_PORT;

void crsf_init(uart_inst_t* uart_port, uint8_t uart_tx, uint8_t uart_rx, void (*users_on_update_rc_channels_callback)(packed_payload_t*)){
    UART_PORT = uart_port;
    uart_init(UART_PORT, 420000);
    gpio_set_function(uart_tx, GPIO_FUNC_UART);
    gpio_set_function(uart_rx, GPIO_FUNC_UART);
    on_update_rc_channels_callback = users_on_update_rc_channels_callback;
}

packed_payload_t* crsf_process_frame_internal(uint8_t* frame){
    uint8_t type = frame[2]; //Type byte in CRSF frame
    
    // Type 0x16 is RC Channels (Joysticks)
    if (type == 0x16) {
        return (packed_payload_t*) &frame[3];
    }
}

void crsf_read_incoming_frames(){
    static uint8_t crsf_buffer[CRSF_MAX_PACKET_LEN];
    static int crsf_curr_frame_index = 0;
    static int crsf_len = 0;

    if (uart_is_readable(UART_PORT)) { //TO DO: MAKE SURE CRC IS CHECKED BEFORE PROCESSING FRAME
        uint8_t next_byte = uart_getc(UART_PORT);

        // State Machine to find packets
        if (crsf_curr_frame_index == 0) {
            // Looking for Sync Byte
            if (next_byte == CRSF_SYNC_BYTE) {
                crsf_buffer[crsf_curr_frame_index++] = next_byte;
            }
        } else if (crsf_curr_frame_index == 1) {
            // Length Byte (Payload length + 2 for Type and CRC)
            crsf_len = next_byte;
            if (crsf_len > 62 || crsf_len < 2) { // Sanity check
                crsf_curr_frame_index = 0; // Invalid length, reset
            } else {
                crsf_buffer[crsf_curr_frame_index++] = next_byte;
            }
        } else {
            // Read rest of packet
            crsf_buffer[crsf_curr_frame_index++] = next_byte;
            // Check if we have received the full packet
            // Total bytes = 1 (Sync) + 1 (Len) + Len
            if (crsf_curr_frame_index >= crsf_len + 2) {
                on_update_rc_channels_callback(crsf_process_frame_internal(crsf_buffer));
                crsf_curr_frame_index = 0; // Reset for next packet
            }
        }
    }
}

void pico_crsf_is_library_accesible(){
    printf("Accessing the pico_crsf library is functioning properly! \n");
}