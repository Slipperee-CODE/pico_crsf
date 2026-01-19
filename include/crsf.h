#pragma once

typedef struct __attribute((packed)){ //if you cast an address to a pointer to this type of struct, accessing struct_pointer->channel0 will access the next 11 bits starting at the address
    unsigned channel0 : 11;
    unsigned channel1 : 11;
} packed_payload_t;
 
void pico_crsf_is_library_accesible();