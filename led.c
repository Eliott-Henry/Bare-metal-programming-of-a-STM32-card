#include <stdint.h>
#include "led.h"
#include "stm32l475xx.h"


void led_init(){
    
    // allumage de la clock du GPIOB et GPIOC de AHB2ENR (p.252 manuel ref)
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;

    // mise à l'état de sortie en mettant [0,1] dans [29, 28]
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14) | (0b01 << GPIO_MODER_MODE14_Pos);
}

// Allume LED2
void led_g_on(){
    // Pin 14 allumé : bit 14 (set à 1). On peut laisser le bit de reset à 1 puisque c'est celui de set qui a la priorité
    GPIOB->BSRR = GPIO_BSRR_BS14;
}

// Eteint LED2
void led_g_off(){
    // Pin 14 à reset donc bit 30 à 1 et bit 14 à 0 dans BSRR
    GPIOB->BSRR = GPIO_BSRR_BR14;
}

void led(state led_state){
    
    if(led_state == LED_OFF){
        // mettre PC9 en entrée
        GPIOC->MODER &= ~GPIO_MODER_MODE9;
    }
    else if(led_state == LED_YELLOW){
        // mettre PC9 en sortie : bits de MODER [19, 18] à [0,1]
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9) | (0b01 << GPIO_MODER_MODE9_Pos);

        // mettre PC9 en haute : bits 9 à 1 dans BSRR
        GPIOC->BSRR |= GPIO_BSRR_BS9;
    }
    else if(led_state == LED_BLUE){
        // mettre PC9 en sortie
        GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9) | (0b01 << GPIO_MODER_MODE9_Pos);
       
        // mettre PC9 en sortie bas : bit 25 à 1 dans BSRR
        GPIOC->BSRR |= GPIO_BSRR_BR9;
    }
}