#include "matrix.h"
#include "stm32l475xx.h"
#include <stdint.h>

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
    deactivate_rows();
    
    // Pour attendre 100ms, on fait au moins 8000 asm volatile(nop), car ils prennent un cycle, et l'horloge est de 80MHz
    for (int i = 0; i < 8000; i++){
        asm volatile("nop");
    }

    RST(1);
    init_bank0();
}

void RST(char c){
    if(c){
        GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD3) | (0b01 << GPIO_ODR_OD3_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD3;
    }
}

void SB(char c){
    if(c){
       GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD5) | (1 << GPIO_ODR_OD5_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD5;
    }
}

void LAT(char c){
    if(c){
        GPIOC->ODR = (GPIOC->ODR & ~GPIO_ODR_OD4) | (1 << GPIO_ODR_OD4_Pos);
    }
    else{
        GPIOC->ODR &= ~GPIO_ODR_OD4;
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
        GPIOA->ODR = (GPIOA->ODR & ~GPIO_ODR_OD4) | (1<< GPIO_ODR_OD4_Pos);
    }
    else{
        GPIOA->ODR &= ~GPIO_ODR_OD4;
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

void pulse_SCK(){
    SCK(0); 
    asm volatile("nop");
    asm volatile("nop");
    SCK(1);
    asm volatile("nop");
    asm volatile("nop");
    SCK(0);
    asm volatile("nop");
    asm volatile("nop");
}

void pulse_LAT(){
    LAT(1);
    asm volatile("nop");
    asm volatile("nop");
    LAT(0);
    asm volatile("nop");
    LAT(1);
    asm volatile("nop");
    asm volatile("nop");
}

void deactivate_rows(){
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    switch(row){
        case(0): 
            ROW0(1);
            break;        
        case(1): 
            ROW1(1);
            break;
        case 2: 
            ROW2(1);
            break;
        case 3: 
            ROW3(1);
            break;
        case 4: 
            ROW4(1);
            break;
        case 5: 
            ROW5(1);
            break;
        case 6: 
            ROW6(1);
            break;
        case 7: 
            ROW7(1);
            break;
    }
}

void send_byte(uint8_t val, int bank){
    SB(bank);
    char c;
    for(int i = 7; i >= 0; i--){
        c = val & (1 << i);
        SDA(c);
        pulse_SCK();
    }
    pulse_LAT();
}

void mat_set_row(int row, const rgb_color *val){
    for(int i = 7; i >= 0; i--){
        send_byte(val[i].b, 1);
        send_byte(val[i].g, 1);
        send_byte(val[i].r, 1);
    }
    activate_row(row);
    pulse_LAT();
}

void init_bank0(){
    send_byte(0b11111111, 0);
    pulse_LAT();
}

void test_pixels(){
    
    rgb_color val[8] = {{0,0,0}};
    
    for(int i = 0; i < 8; i++){
        deactivate_rows();
       
        for(int j = 0; j < 8; j++){
            val[j].r = 255;
            val[j].b = j*30;
            val[j].g = j*30;
        }
        mat_set_row(i, val);

        for(int k = 0; k < 10000000; k++){
            asm volatile("nop");
        }

        for(int j = 0; j < 8; j++){
            val[j].r = j*30;
            val[j].b = 255;
            val[j].g = j*30;
        }
        mat_set_row(i, val);

        for(int k = 0; k < 10000000; k++){
            asm volatile("nop");
        }

        for(int j = 0; j < 8; j++){
            val[j].r = j*30;
            val[j].b = j*30;
            val[j].g = 255;
        }
        mat_set_row(i, val);

        for(int k = 0; k < 10000000; k++){
            asm volatile("nop");
        }

        for(int k = 0; k < 1000000; k++){
            asm volatile("nop");
        }
    }
}