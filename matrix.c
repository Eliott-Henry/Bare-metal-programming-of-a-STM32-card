#include "matrix.h"
#include "stm32l475xx.h"

void matrix_init(){
    // allumage des clocks de GPIO A B et C
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOAEN;

    // on met toutes les pins des ports concernés par le driver en mode output
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2) | (0b01 << GPIO_MODER_MODE2_Pos);    
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3) | (0b01 << GPIO_MODER_MODE3_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4) | (0b01 << GPIO_MODER_MODE4_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5) | (0b01 << GPIO_MODER_MODE5_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6) | (0b01 << GPIO_MODER_MODE6_Pos);
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7) | (0b01 << GPIO_MODER_MODE7_Pos);    
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15) | (0b01 << GPIO_MODER_MODE15_Pos);
    
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0) | (0b01 << GPIO_MODER_MODE0_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1) | (0b01 << GPIO_MODER_MODE1_Pos);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2) | (0b01 << GPIO_MODER_MODE2_Pos);

    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3) | (0b01 << GPIO_MODER_MODE3_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4) | (0b01 << GPIO_MODER_MODE4_Pos);
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5) | (0b01 << GPIO_MODER_MODE5_Pos);

    // on met toutes les pins concernées en mode very high speed
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2) | (0b11 << GPIO_OSPEEDR_OSPEED2_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3) | (0b11 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4) | (0b11 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5) | (0b11 << GPIO_OSPEEDR_OSPEED5_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED6) | (0b11 << GPIO_OSPEEDR_OSPEED6_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED7) | (0b11 << GPIO_OSPEEDR_OSPEED7_Pos);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED15) | (0b11 << GPIO_OSPEEDR_OSPEED15_Pos);

    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0) | (0b11 << GPIO_OSPEEDR_OSPEED0_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED1) | (0b11 << GPIO_OSPEEDR_OSPEED1_Pos);
    GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2) | (0b11 << GPIO_OSPEEDR_OSPEED2_Pos);

    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3) | (0b11 << GPIO_OSPEEDR_OSPEED3_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4) | (0b11 << GPIO_OSPEEDR_OSPEED4_Pos);
    GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5) | (0b11 << GPIO_OSPEEDR_OSPEED5_Pos);

    // Initialisation de certaines broches :
    /*
    RST : 0 (reset le DM163) (PC3)
    LAT : 1 (PC4)
    SB : 1 (PC5)
    
    SCK et SDA : 0 (PB1 PA4)
    C0 à C7 : 0 (éteint toutes les lignes) (PB2 PA15 PA2 PA7 PA6 PA5 PB0 PA3)
    */

    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
    
    // Pour attendre 100ms, on fait au moins 8000 asm volatile(nop), car ils prennent un cycle, et l'horloge est de 80MHz
    for (int i = 0; i < 8000; i++){
        asm volatile("nop");
    }

    RST(1);
}

void RST(char c){
    if(c){
        GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD3) | (1 << GPIO_ODR_OD3_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD3;
    }
}

void SB(char c){
    if(c){
       GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD4) | (1 << GPIO_ODR_OD4_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD4;
    }
}

void LAT(char c){
    if(c){
        GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD5) | (1 << GPIO_ODR_OD5_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD5;
    }
}

void SCK(char c){
    if(c){
        GPIOB->ODR = (GPIOB->ODR & ~GPIO_ODR_OD1) | (1 << GPIO_ODR_OD1_Pos);
    }
    else{
        GPIOB->ODR &= ~GPIO_ODR_OD1;
    }
}

void SDA(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD4) | (1<< GPIO_ODR_OD4);
    }
    else{
        GPIOB->ODR &= ~GPIO_ODR_OD4;
    }
}

void ROW0(char c){
    if(c){
        GPIOB->ODR = (GPIOB->ODR & ~GPIO_ODR_OD2) | (1<< GPIO_ODR_OD2_Pos);
    }
    else{
        GPIOB->ODR &= ~GPIO_ODR_OD2;
    }
}

void ROW1(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD15) | (1<< GPIO_ODR_OD15_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD15;
    }
}

void ROW2(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD2) | (1<< GPIO_ODR_OD2_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD2;
    }
}

void ROW3(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD7) | (1<< GPIO_ODR_OD7_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD7;
    }
}

void ROW4(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD6) | (1<< GPIO_ODR_OD6_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD6;
    }
}

void ROW5(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD5) | (1<< GPIO_ODR_OD5_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD5;
    }
}

void ROW6(char c){
    if(c){
        GPIOB->ODR = (GPIOB->ODR & ~GPIO_ODR_OD0) | (1<< GPIO_ODR_OD0_Pos);
    }
    else{
        GPIOB->ODR &= ~GPIO_ODR_OD0;
    }
}

void ROW7(char c){
    if(c){
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD3) | (1<< GPIO_ODR_OD3_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD3;
    }
}