#include "led.h"
#include "uart.h"
#include "clocks.h"
#include "matrix.h"
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
    //uart_init();
    matrix_init();
    //test_pixels();
    test_static();
    //led_init();
    return 0;
}