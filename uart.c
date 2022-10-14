#include "stm32l475xx.h"
#include "stm32l4xx.h"
#include "uart.h"

// Read USART Description p.1335

void uart_init(){
    // USART1_RX port B : MODE 7 de GPIOB à 10 (PB7)
    GPIOB->MODER = (GPIOB->MODER | GPIO_MODER_MODE7_1) & ~GPIO_MODER_MODE7_0;
    // USART1_TX port B : MODE 6 de GPIOB à 10 (PB6)
    GPIOB->MODER = (GPIOB->MODER | GPIO_MODER_MODE6_1) & ~GPIO_MODER_MODE6_0;
    // Clock GPIOB enable
    RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;

    // Pour trouver AFRL correspondant, datasheet p.70 : 
    // PB6 : USART1_TX = AF7
    // PB7 : USART1-RX = AF7 
    // On va mettre AF7 (donc 0111) dans AFSEL 6 et AFSEL7 de GPIOB_AFRL
    // /!\ Est-ce que AFRL correspond bien à la première case du tableau AFR?
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL6) & ~GPIO_AFRL_AFSEL6_3;
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL7) & ~GPIO_AFRL_AFSEL7_3;

    // USART1 clock enable : RCC_APB2ENR au bit USART1EN
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;// Oversampling : on le choisit dans USART_CR1 (on veut lemettre à 16 ici)sk;

    // Reset série USART1
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST_Msk;

    // Vitesse USART1 : il faut modifier BRR, et pour ça choisir USARTDIV (calcul p. 1349)
    // fCK de l'USART (Dans RCC, nous on l'a mise à PCLK : 80MHz d'après le TP grâce au fichier clocks)
    // On veut prendre 16 en oversampling dans la suite donc ça donne BRR = USARTDIV = 694.444(décimal) ~= 694(décimal) = 0x2C6 (cat OVER8=0, oversampling 16)
    uint16_t brr = 0x2C6; 
    USART1->BRR = brr;
    // /!\ Est-ce que ça met bien le nombre dans les bits [15:0] sans toucher aux [31:16] ?

    // mettre en mode oversampling 16
    USART1->CR1 &= ~USART_CR1_OVER8_Msk; 

    // Mettre la taille des mots à 8 bits : il faut mettre M[1:0] à 00 
    USART1->CR1 &= (~USART_CR1_M0_Msk & ~USART_CR1_M1_Msk);

    // Mettre le bit de parité PCE à 0
    USART1->CR1 &= ~USART_CR1_PCE_Msk;

    // Mettre le bit de stop à 1 : dans USART_CR2 il faut mettre STOP[1,0] à 00
    USART1->CR2 &= ~USART_CR2_STOP_Msk;

    // Activer l'USART1, le transmetteur et le récepteur
    USART1->CR1 = (USART1->CR1 | USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}

void uart_putchar(uint8_t c){
    // je crois qu'on a besoin 
    if(READ_BIT(USART1->ISR, USART_ISR_TEACK) && READ_BIT(USART1->ISR, USART_ISR_TXE)){
        // normalement ça écrit bien seulement sur les 8 bits de poids faible
        USART1->TDR = c;
    }
}