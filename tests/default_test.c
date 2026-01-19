#include <stdio.h>
#include "pico/stdlib.h"
#include "crsf.h"

int main()
{
    stdio_init_all();
    
    while (true) {
        printf("This loop prints the first 8 received channel values! \n");
        pico_crsf_is_library_accesible();
        //printf("Acceleration along x-axis is %d gs\n", accelerometer_get_x());
    }
}