/* Includes */
#include "stm32g0xx.h"


/*
 * Entradas :
 *    BOTÃO 1 - PB5
 *    BOTÃO 2 - PB4
 *    BOTÃO 3 - PB3
 * Saidas
 *    led1 - PB8
 *    led2 - PB9
 *    led3 - PB10
 *
 * Tarefa
 *
 * BOTÕES			 LED
 *   0			   apagado
 * 	 1				 Azul
 * 	 2			    Verde
 * 	 3			 Ciano (Vd+Az)
 * 	 4			   Vermelho
 * 	 5			Magenta (Vm+Az)
 * 	 6			Amarelo (Vm+Vd)
 * 	 7		   Branco (Vm+Vd+Az)
 *
 */

uint16_t botoes=0;

int main(void)
{

	// Configurando GPIOs

	RCC->IOPENR=0x0000003F; //habilita clock das portas

	GPIOB->MODER&=~(GPIO_MODER_MODER3|GPIO_MODER_MODER4|GPIO_MODER_MODER5); //entrada

	GPIOB->MODER&=~(GPIO_MODER_MODER8|GPIO_MODER_MODER9|GPIO_MODER_MODER10);
	GPIOB->MODER|=(GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0|GPIO_MODER_MODER10_0); //saída

	//pull-down
	GPIOB->PUPDR |=(GPIO_PUPDR_PUPDR8_0|GPIO_PUPDR_PUPDR9_0|GPIO_PUPDR_PUPDR10_0); //leds
	GPIOB->PUPDR &=~(GPIO_PUPDR_PUPDR8|GPIO_PUPDR_PUPDR9|GPIO_PUPDR_PUPDR10);

	GPIOB->PUPDR |=(GPIO_PUPDR_PUPDR3_0|GPIO_PUPDR_PUPDR4_0|GPIO_PUPDR_PUPDR5_0); //botoes
	GPIOB->PUPDR &=~(GPIO_PUPDR_PUPDR3|GPIO_PUPDR_PUPDR4|GPIO_PUPDR_PUPDR5);

  /* Infinite loop */
  while (1)
  {
botoes=GPIOB->IDR & (GPIO_IDR_IDR_5|GPIO_IDR_IDR_4|GPIO_IDR_IDR_3);
botoes=botoes>>3;

switch(botoes){
case 0:
	GPIOB->ODR&=~(GPIO_ODR_ODR_8|GPIO_ODR_ODR_9|GPIO_ODR_ODR_10);
	break;
case 1:
	GPIOB->ODR|=GPIO_ODR_ODR_10;
	GPIOB->ODR&=~(GPIO_ODR_ODR_8|GPIO_ODR_ODR_9);
	break;
case 2:
	GPIOB->ODR|=GPIO_ODR_ODR_9;
	GPIOB->ODR&=~(GPIO_ODR_ODR_8|GPIO_ODR_ODR_10);
		break;
case 3:
	GPIOB->ODR|=(GPIO_ODR_ODR_9|GPIO_ODR_ODR_10);
	GPIOB->ODR&=~(GPIO_ODR_ODR_8);
	break;
case 4:
	GPIOB->ODR|=(GPIO_ODR_ODR_8);
	GPIOB->ODR&=~(GPIO_ODR_ODR_9|GPIO_ODR_ODR_10);
	break;
case 5:
	GPIOB->ODR|=(GPIO_ODR_ODR_8|GPIO_ODR_ODR_10);
	GPIOB->ODR&=~(GPIO_ODR_ODR_9);
	break;
case 6:
	GPIOB->ODR|=(GPIO_ODR_ODR_8|GPIO_ODR_ODR_9);
	GPIOB->ODR&=~(GPIO_ODR_ODR_10);
	break;
case 7:
	GPIOB->ODR|=(GPIO_ODR_ODR_8|GPIO_ODR_ODR_9|GPIO_ODR_ODR_10);
	break;
}
  }
}

