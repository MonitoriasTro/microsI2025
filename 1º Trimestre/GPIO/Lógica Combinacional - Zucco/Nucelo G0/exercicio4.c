/* Includes */
#include "stm32g0xx.h"


/*
 * Entradas :
 *    BOTÃO 1 - PA0
 *    BOTÃO 2 - PA1
 *    BOTÃO 3 - PB8
 *    BOTÃO 4 - PB9
 * Saidas:
 *    led Vd - PA4
 *    led Am - PB10
 *
 *
 * Tarefa
 *
 * led verde - acender - todas as chaves estiverem na mesma posição
 * led amarelo - acender somente quando uma das chaves de cada conjunto não está na mesma posição
 *
 */

uint16_t botoesB=0;
uint16_t botoesA=0;

int main(void)
{

	// Configurando GPIOs
	// ativando clock de todos os GPIOs
	RCC->IOPENR=0x0000003F;

	// Configurando GPIOB -- PB8 a PB9 como entrada,  PB10 como saída
	GPIOB->MODER &= ~GPIO_MODER_MODE10;
	GPIOB->MODER |= GPIO_MODER_MODE10_0; //saida

	GPIOB->MODER &= ~(GPIO_MODER_MODE8|GPIO_MODER_MODE9); //entrada

	// Configurando GPIOA -- PA0 a PA1 como entrada,  PA4 como saída
	GPIOA->MODER &= ~GPIO_MODER_MODE4;
	GPIOA->MODER |= GPIO_MODER_MODE4_0; //saida

	GPIOA->MODER &= ~(GPIO_MODER_MODE0|GPIO_MODER_MODE1); //entrada

	//pull-up (01) para as entradas PA0, PA1, PB8 e PB9
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD0|GPIO_PUPDR_PUPD1);
	GPIOA->PUPDR |=(GPIO_PUPDR_PUPD0_0|GPIO_PUPDR_PUPD1_0);

	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD8|GPIO_PUPDR_PUPD9);
	GPIOB->PUPDR |=(GPIO_PUPDR_PUPD8_0|GPIO_PUPDR_PUPD9_0);

	/* Infinite loop */
	while (1)
	{
		// Lendo as entradas
		botoesA=GPIOA->IDR & (GPIO_IDR_ID0|GPIO_IDR_ID1);
		botoesB=GPIOB->IDR & (GPIO_IDR_ID8|GPIO_IDR_ID9);
	
		botoesB=botoesB>>8;
	
		//se todas as chaves estiverem na mesma posição - ligar led verde
		if((botoesA==0b00 && botoesB==0b00)|| (botoesA==0b11 && botoesB==0b11)){
			GPIOA->ODR&=~GPIO_ODR_OD4; //led amarelo em 0
			GPIOB->ODR|=GPIO_ODR_OD10; //led verde em 1
		}
	
		//se somente uma chave estiver diferente - ligar led amarelo
		else if((botoesB==0b10 && botoesA==0b00) || (botoesB==0b10 && botoesA==0b11) || (botoesB==0b01 && botoesA==0b00) || (botoesB==0b01 && botoesA==0b11) || (botoesB==0b00 && botoesA==0b10) || (botoesB==0b11 && botoesA==0b10) || (botoesB==0b00 && botoesA==0b01) || (botoesB==0b11 && botoesA==0b01)){
			GPIOA->ODR|=GPIO_ODR_OD4; 	//led amarelo em 1
			GPIOB->ODR&=~GPIO_ODR_OD10; //led verde em 0
	 	}
			
	  	else{
			GPIOA->ODR&=~GPIO_ODR_OD4; //led amarelo em 0
			GPIOB->ODR&=~GPIO_ODR_OD10;//led verde em 0
	  	}
	}
}
