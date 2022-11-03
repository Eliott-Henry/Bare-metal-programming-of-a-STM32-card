
#include <stdint.h>
extern uint8_t __bss_start, __bss_end;

void init_bss(){
    uint8_t * p = &__bss_start;
    while(p < &__bss_end){
        *p = 0;
        p++;
    }
}