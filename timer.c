#include "timer.h"
#include "stm32l475xx.h"
#include "led.h"
#include "matrix.h"

void timer_init(int max_us){

    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    
    // Reset TIM2_SR
    // Reset du counter
    TIM2->CNT = 0;
    TIM2->SR = (TIM2->SR &~ TIM_SR_CC4OF &~TIM_SR_CC3OF &~TIM_SR_CC2OF &~TIM_SR_CC1OF &~TIM_SR_TIF &~TIM_SR_CC4IF &~TIM_SR_CC3IF &~TIM_SR_CC2IF &~TIM_SR_CC1IF &~TIM_SR_UIF);

    // On met la DIR à 0 donc en mode upcounting
    TIM2->CR1 = (TIM2->CR1 & ~TIM_CR1_DIR);


    // Il faut PSC contienne 79 car fck_psc = 80MHz et on veut fck_psc / (PSC + 1) = 1MHz
    TIM2->PSC = 79;

    // Auto-reload value
    TIM2->ARR = max_us;

    // Interrupt enable pour timer reset
    TIM2->DIER |= TIM_DIER_UIE;

    // activation des irq de TIM2
    NVIC_EnableIRQ(28);

    // activation du compteur
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(){
    // si la led verte est allumée
    TIM2->SR &= ~ TIM_SR_UIF;
    print_line_matrix();
}