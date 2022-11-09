#include "led.h"
#include "uart.h"
#include "clocks.h"
#include "matrix.h"
#include <stdint.h>
#include <stddef.h>
#include "irq.h"
#include "buttons.h"
#include "timer.h"

int main(){
    clocks_init();
    led_init();
    irq_init();
    button_init();
    uart_init(38400);
    // On donne le compteur max en microsecondes (de manière à afficher 60 fois toute l'image par seconde) et on modifie un peu pour bien afficher l'image des trames
    timer_init(1099900/(60*8));
    matrix_init();
    //test_static();   
    return 0;
}