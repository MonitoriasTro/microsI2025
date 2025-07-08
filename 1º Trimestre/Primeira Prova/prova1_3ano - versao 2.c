/* Includes */
#include "stm32g0xx.h"


/*
 * Entradas :
 *   sw0	PB4
 *   sw1	PB5
 *   sw2	PB8
 *   sw3	PB9
 *
 *   Ativos em LOW
 *
 * Saidas:
 *  Ld0		PA0
 *  Ld1		PA1
 *  Ld2		PA6
 *  Ld3		PA7
 *
 * Tarefa
 *
 *  X=Y=0 	   -> led0
 *  X=Y  	   -> led1
 *  X>Y  	   -> led2
 *  X=0 ou Y=0 -> led3
 *
 */

uint16_t x=0, y=0;

int main(void)
{

	// Configurando GPIOs
	// ativando clock de todos os GPIOs
	RCC->IOPENR=0x0000003F;
	GPIOA->MODER |= 0x28000000;

	//entradas (00)
	GPIOB->MODER=0b00000000000000000000;

	//saidas (01)
	GPIOA->MODER&=~(GPIO_MODER_MODE0|GPIO_MODER_MODE1|GPIO_MODER_MODE6|GPIO_MODER_MODE7);
	GPIOA->MODER|=(GPIO_MODER_MODE0_0|GPIO_MODER_MODE1_0|GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0);

	//GPIOA->MODER &= ~(0xF00F);
	//GPIOA->MODER |= 0x5005;


	/* Infinite loop */
	while (1)
	{
		// Lendo as entradas
		x=(GPIOB->IDR & 0b1100000000)>>8;
		y=(GPIOB->IDR & 0b0000110000)>>4;


		if(x==y){
			if(x==0 && y==0){
				GPIOA->ODR|=(GPIO_ODR_OD0|GPIO_ODR_OD1); //os dois estao em zero e tambem sao iguais - ld0 e ld1
				GPIOA->ODR&=~(GPIO_ODR_OD6|GPIO_ODR_OD7);
			}
			else{
				GPIOA->ODR|=(GPIO_ODR_OD1); //as entradas sao iguais - ld1
				GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD6|GPIO_ODR_OD7);
			}
		}

		if(x>y){
			if(x==0 || y==0){
				GPIOA->ODR|=(GPIO_ODR_OD6|GPIO_ODR_OD7); //alguma das entradas vale zero - ld3
				GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1);
			}
			else{
				GPIOA->ODR|=(GPIO_ODR_OD6); //x vale mais que y - ld2
				GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1|GPIO_ODR_OD7);
			}
		}
		else if(x==0 || y==0){
				GPIOA->ODR|=(GPIO_ODR_OD7); //alguma das entradas vale zero - ld3
				GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1|GPIO_ODR_OD6);
			}
		}

}


