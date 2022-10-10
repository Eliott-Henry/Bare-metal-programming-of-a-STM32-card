#include "led.h"

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
    //return fibo(8);
    
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