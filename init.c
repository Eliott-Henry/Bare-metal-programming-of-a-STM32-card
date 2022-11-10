
#include <stdint.h>
extern uint8_t __bss_start, __bss_end, __data_start, __data_end, _start_data_flash;

void init_bss(){
    uint8_t * p = &__bss_start;
    while(p < &__bss_end){
        *p = 0;
        p++;
    }
}

void init_data(){
    uint8_t * p = &__data_start;
    uint8_t *q = &_start_data_flash;
    while(p< &__data_end){
        *p = *q;
        p++;
        q++;
    }
}