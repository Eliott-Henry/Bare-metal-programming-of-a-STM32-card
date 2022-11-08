#include "led.h"
#include "uart.h"
#include "clocks.h"
#include "matrix.h"
#include <stdint.h>
#include <stddef.h>
#include "irq.h"
#include "buttons.h"
#include "timer.h"

int fibo(int n){
    
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }

    return fibo(n-1) + fibo(n-2);
}

int main(){
    clocks_init();
    led_init();
    irq_init();
    button_init();
    uart_init(38400);
    // On donne le compteur max en microsecondes (de manière à afficher 60 fois toute l'image par seconde)
    timer_init(1000000/(60*8));
    matrix_init();
    //test_pixels();
    //test_static();
    
    return 0;
}