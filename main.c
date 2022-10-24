#include "led.h"
#include "uart.h"
#include "clocks.h"
#include "matrix.h"
#include <stdint.h>
#include <stddef.h>

uint32_t sum;

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
    uart_init();
    matrix_init();

    led_init();
    for(int i = 0; i < 100000;i++){
        led(LED_OFF);
        led_g_on();
        for(int k = 0; k < 1000000; k++){
            asm volatile("nop");
        }
        led_g_off();
        led(LED_YELLOW);
        for(int k = 0; k < 1000000; k++){
            asm volatile("nop");
        }
        led(LED_BLUE);
        for(int k = 0; k < 1000000; k++){
            asm volatile("nop");
        }
    }

    return 0;
}