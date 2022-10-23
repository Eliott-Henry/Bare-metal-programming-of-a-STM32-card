#include "led.h"
#include "uart.h"
#include "clocks.h"
#include <stdint.h>
#include <stddef.h>

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
    //return fibo(8); (Test Fibo)
    //uart_init();
    //uart_putchar('H');
    //uart_putchar('e');
    //uart_puts("Hello World!");

    /*
    Tests puts : on écrit une chaîne de 10 caractères et l'uart nous la renvoie
    
    char *s = "abcdefghij";
    size_t size = 10;
    
    while(1){
        uart_gets(s, size);
        uart_puts(s);
    }*/

    uint32_t sum = uart_checksum(1000);
    sum = sum + 1;

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