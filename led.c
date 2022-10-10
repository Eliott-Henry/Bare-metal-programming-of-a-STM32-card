#include <stdint.h>
#include "led.h"

// Adresses définies p.77

// Origin = 0x40021000
#define RCC_AHB2ENR *((volatile uint32_t*) 0x4002104C) // offset = 0x4C

// Origin = 0x48000400
#define GPIOB_MODER *((volatile uint32_t*) 0x48000400) // offset = 0
#define GPIOB_BSRR *((volatile uint32_t*) 0x48000418) // offset = 0x18

void led_init(){
    
    // allumage de la clock du GPIOB de AHB2ENR (p.252 manuel ref)
    RCC_AHB2ENR = (RCC_AHB2ENR | 0b110);

    // mise à l'état de sortie en mettant [0,1] dans [29, 28]
    GPIOB_MODER = ((GPIOB_MODER & ~(1<<29)) | (1<<28));
}

// ~(0b11<<28)) | (0b01<<28)

// Allume LED2
void led_g_on(){
    // Pin 14 allumé : bit 14 (set à 1). On peut laisser le bit de reset à 1 puisque c'est celui de set qui a la priorité
    GPIOB_BSRR = (1 << 14); 
}

// Eteint LED2
void led_g_off(){
    // Pin 14 à reset donc bit 30 à 1 et bit 14 à 0
    GPIOB_BSRR = (1<<30);
}