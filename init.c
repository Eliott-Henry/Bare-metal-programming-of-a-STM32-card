
#include <stdint.h>
extern uint8_t __bss_start, __bss_end;
//uint8_t a; // va dans la bss 

void init_bss(){
    uint8_t * p = &__bss_start;
    while(p < &__bss_end){
        *p = 0;
        p++;
    }
    //a = a + 1; // pour reconnaître les instructions en debug et vérifier que a vaut bien 0 au début
}