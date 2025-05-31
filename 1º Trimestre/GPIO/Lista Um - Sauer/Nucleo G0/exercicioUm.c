#include "stm32g0xx.h"

int main(){
	RCC->IOPENR = 0x0000003F;  //habilita o clock de todos os io's
	GPIOB->MODER = 0x00001555; //saidas: PB0 a PB6; entradas: PB7 a PB9
	GPIOB->PUPDR = 0x000A8000; 

	while (1) {
		int i = (GPIOB->IDR&0x380)>>7;
		switch(i) {
			case 0:
				GPIOB->ODR = 0x0000;
				break;
			case 1:
				GPIOB->ODR = 0x0001;
				break;
			case 2:
				GPIOB->ODR = 0x0003;
				break;
			case 3:
				GPIOB->ODR = 0x0007;
				break;
			case 4:
				GPIOB->ODR = 0x000F;
				break;
			case 5:
				GPIOB->ODR = 0x001F;
				break;
			case 6:
				GPIOB->ODR = 0x003F;
				break;
			case 7:
				GPIOB->ODR = 0x007F;
				break;
			default:
				GPIOB->ODR = 0x0000;
				break;
		}
	}
}
