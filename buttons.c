#include "stm32l475xx.h"
#include "buttons.h"
#include "led.h"
#include "matrix.h"

void button_init(void){
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN;
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE13) | (0b00 << GPIO_MODER_MODE13_Pos);
    
    // On sélectionne la pin PC 13 pour les interruptions
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13) | (0b0010 << SYSCFG_EXTICR4_EXTI13_Pos);
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    // on active seulement l'interruption sur les fronts descendants
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;
    
    // numéro d'irq interne de EXTI15_10 donc de EXTI13 
    NVIC_EnableIRQ(40);
}

void EXTI15_10_IRQHandler(){
    
    EXTI->PR1 |= EXTI_PR1_PIF13;

    // si la led verte est allumée
    if(GPIOB->ODR & GPIO_ODR_OD14){
        led_g_off();
    }
    else{
        led_g_on();
    }
}