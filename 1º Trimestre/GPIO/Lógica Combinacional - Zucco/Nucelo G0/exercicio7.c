/* Includes */
#include "stm32g0xx.h"


/*
 * Entradas :
 *    BOTÃO 1 - PB0
 *    BOTÃO 2 - PB1
 *    BOTÃO 3 - PB2
 *    BOTÃO 4 - PB3
 *
 * Saidas:
 *  a	 PC0
 * 	b	 PC1
 * 	c	 PC2
 * 	d	 PC3
 * 	e	 PC4
 * 	f	 PC5
 * 	g	 PC6
 * 	pt	 PC7
 *
 * Tarefa
 *
 *  Elabore um programa que exiba no display o valor numérico do dígito
 * hexadecimal correspondente ao valor expresso pelas chaves.
 *
 */

uint16_t botoes=0;
uint16_t display[16]={0b00111111, 0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b0000111,0b01111111,0b01101111,0b01110111,0b01111100,0b00111001,0b01011110,0b01111001,0b01110001};
int main(void)
{

	// Configurando GPIOs
	// ativando clock de todos os GPIOs
	RCC->IOPENR=0x0000003F;

	// Configurando GPIOB -- PB0 a PB3 como entrada (botoes)

	GPIOB->MODER &= ~(GPIO_MODER_MODE0|GPIO_MODER_MODE1|GPIO_MODER_MODE2|GPIO_MODER_MODE3); //entrada

	// Configurando GPIOC -- PC0 a PC7 como saida (segmentos do display)
	GPIOC->MODER &=~(GPIO_MODER_MODE0|GPIO_MODER_MODE1|GPIO_MODER_MODE2|GPIO_MODER_MODE3|GPIO_MODER_MODE4|GPIO_MODER_MODE5|GPIO_MODER_MODE6|GPIO_MODER_MODE7);
	GPIOC->MODER |= (GPIO_MODER_MODE0_0|GPIO_MODER_MODE1_0|GPIO_MODER_MODE2_0|GPIO_MODER_MODE3_0|GPIO_MODER_MODE4_0|GPIO_MODER_MODE5_0|GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0);


	//pull-up (01) para as entradas PB0-PB3
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0|GPIO_PUPDR_PUPD1|GPIO_PUPDR_PUPD2|GPIO_PUPDR_PUPD3);
	GPIOA->PUPDR |=(GPIO_PUPDR_PUPD0_0|GPIO_PUPDR_PUPD1_0|GPIO_PUPDR_PUPD2_0|GPIO_PUPDR_PUPD3_0);


  /* Infinite loop */
  while (1)
  {
	  // Lendo as entradas
	  botoes=GPIOB->IDR & (GPIO_IDR_ID0|GPIO_IDR_ID1|GPIO_IDR_ID2|GPIO_IDR_ID3);

	  GPIOC->ODR=display[botoes];


  }
}

