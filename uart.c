#include "stm32l475xx.h"
#include "stm32l4xx.h"
#include "uart.h"
#include <stddef.h>
// Read USART Description p.1335

void uart_init(int baudrate){

    // Clock GPIOB enable
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    
    // USART1_RX port B : MODE 7 de GPIOB à 10 (PB7)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7) | (0b10 << GPIO_MODER_MODE7_Pos);
    
    // USART1_TX port B : MODE 6 de GPIOB à 10 (PB6)
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6) | (0b10 << GPIO_MODER_MODE6_Pos);

    // Pour trouver AFRL correspondant, datasheet p.70 : 
    // PB6 : USART1_TX = AF7
    // PB7 : USART1-RX = AF7 
    // On va mettre AF7 (donc 0111) dans AFSEL 6 et AFSEL7 de GPIOB_AFRL
    // /!\ Est-ce que AFRL correspond bien à la première case du tableau AFR?
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6) |(0x7 << GPIO_AFRL_AFSEL6_Pos);
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7) |(0x7 << GPIO_AFRL_AFSEL7_Pos);

    // USART1 clock enable : RCC_APB2ENR au bit USART1EN
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;// Oversampling : on le choisit dans USART_CR1 (on veut lemettre à 16 ici)sk;

    // Reset série USART1
    RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    // ICI REVOIR LES BITS QUI N'ONT PAS BESOIN D'ETRE MODIFIES (grâce au reset)

    // Vitesse USART1 : il faut modifier BRR, et pour ça choisir USARTDIV (calcul p. 1349)
    // fCK de l'USART (Dans RCC, nous on l'a mise à PCLK : 80MHz d'après le TP grâce à clocks_init)
    // On veut prendre 16 en oversampling dans la suite donc ça donne BRR = USARTDIV = 80000000/115200 (car OVER8=0, oversampling 16)
    USART1->BRR = 80000000/baudrate;

    // Mettre en mode oversampling 16 : mettre OVER8 à 0 (déjà faut au reset)
    // Mettre la taille des mots à 8 bits : il faut mettre M[1:0] à 00 (déjà fait au reset)
    // Mettre le bit de parité PCE à 0 (déjà fait au reset)
    // Mettre le bit de stop à 1 : dans USART_CR2 il faut mettre STOP[1,0] à 00 (déjà fait au reset)

    // Activer l'USART1, le transmetteur et le récepteur
    USART1->CR1 = (USART1->CR1 | USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}

void uart_putchar(uint8_t c){
    while(!(USART1->ISR & USART_ISR_TXE)) ;
    USART1->TDR = c;
}

uint8_t uart_getchar(){
    while(!(USART1->ISR & USART_ISR_RXNE));
    uint8_t c = USART1->RDR;
    return c;
}

void uart_puts(const char *s){
    while (*s!='\0'){
        uart_putchar(*s);
        s++;
    }
    uart_putchar('\n');
}

void uart_gets(char *s, size_t size){
    for(int i = 0; (size_t)i < size; i++){
        *s = uart_getchar();
        s++;
    }
}

uint32_t uart_checksum(int nb_bits){
    uint32_t s = 0;
    for(int i = 0; i < nb_bits; i++){
        s += uart_getchar();
    }
    return s;
}
