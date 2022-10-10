#include <stdint.h>
#include "led.h"
#include "stm32l475xx.h"

// Adresses définies p.77

// Origin = 0x40021000
#define RCC_AHB2ENR *((volatile uint32_t*) 0x4002104C) // offset = 0x4C

// Origin = 0x48000400
#define GPIOB_MODER *((volatile uint32_t*) 0x48000400) // offset = 0
#define GPIOB_BSRR *((volatile uint32_t*) 0x48000418) // offset = 0x18

// origin = 0x4800 0800
#define GPIOC_MODER *((volatile uint32_t*) 0x48000800) // offset = 0
#define GPIOC_BSRR *((volatile uint32_t*) 0x48000818) // offset = 0x18

void led_init(){
    
    // allumage de la clock du GPIOB et GPIOC de AHB2ENR (p.252 manuel ref)
    RCC_AHB2ENR = (RCC_AHB2ENR | 0b110);

    // mise à l'état de sortie en mettant [0,1] dans [29, 28]
    GPIOB_MODER = ((GPIOB_MODER & ~(1<<29)) | (1<<28));
}

// Allume LED2
void led_g_on(){
    // Pin 14 allumé : bit 14 (set à 1). On peut laisser le bit de reset à 1 puisque c'est celui de set qui a la priorité
    GPIOB_BSRR = (1 << 14); 
}

// Eteint LED2
void led_g_off(){
    // Pin 14 à reset donc bit 30 à 1 et bit 14 à 0 dans BSRR
    GPIOB_BSRR = (1<<30);
}

void led(state led_state){
    
    if(led_state == LED_OFF){
        // mettre PC9 en entrée
        GPIOC_MODER = GPIOC_MODER & ~(0b11 << 18);//mettre 00 dans les bits 18-19 de MODER
    }
    else if(led_state == LED_YELLOW){
        // mettre PC9 en sortie : bits de MODER [19, 18] à [0,1]
        GPIOC_MODER = (GPIOC_MODER & ~(1<<19)) | (1<<18);
        // mettre PC9 en haute : bits 9 à 1 dans BSRR
        GPIOC_BSRR = (1<<9);
    }
    else if(led_state == LED_BLUE){
        // mettre PC9 en sortie
        GPIOC_MODER = (GPIOC_MODER & ~(1<<19)) | (1<<18);
        // mettre PC9 en sortie bas : bit 25 à 1 dans BSRR
        GPIOC_BSRR = (1<<25);
    }
}