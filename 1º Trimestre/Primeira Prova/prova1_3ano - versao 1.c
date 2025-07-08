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
 *  Ld0<2
 *  Ld1<5
 *  Ld2<8
 *  Ld3<15
 *
 */

uint16_t z=0, z1=0, z2=0;

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
	  z1=GPIOB->IDR & 0b1100000000;
	  z2=GPIOB->IDR & 0b0000110000;

	  z1=z1>>6;
	  z2=z2>>4;
	  z=z1+z2;

	  if(z<2){
		  GPIOA->ODR|=(GPIO_ODR_OD0|GPIO_ODR_OD1|GPIO_ODR_OD6|GPIO_ODR_OD7); //led0, led1, led2, led3
	  }

	  if(z<5 && z>2){
		  GPIOA->ODR|=(GPIO_ODR_OD1|GPIO_ODR_OD6|GPIO_ODR_OD7);//led1, led2, led3
		  GPIOA->ODR&=~(GPIO_ODR_OD0);
	  }

	  if(z<8 && z>5){
		  GPIOA->ODR|=(GPIO_ODR_OD6|GPIO_ODR_OD7);// led2, led3
		  GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1);
	  }

	  if(z<15 && z>8){
		  GPIOA->ODR|=(GPIO_ODR_OD7); //led3
		  GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1|GPIO_ODR_OD6);
	  }
	  else{
		  GPIOA->ODR&=~(GPIO_ODR_OD0|GPIO_ODR_OD1|GPIO_ODR_OD6|GPIO_ODR_OD7); //nenhnuma
	  }

  }
}

