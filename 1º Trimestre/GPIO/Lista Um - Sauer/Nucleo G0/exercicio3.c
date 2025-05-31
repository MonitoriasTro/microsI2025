#include "stm32g0xx.h"

int main(){
	RCC->IOPENR = 0x0000003F;  //habilita o clock de todos os io's
	GPIOB->MODER = 0x00005555; //saidas: PB0 a PB6; entradas: PB7 a PB10
	GPIOB->PUPDR = 0x002A8000; //entradas com pull down interno

	while (1) {
		int i = (GPIOB->IDR&0x180)>>7; //entradas PB7 e PB8
		int j = (GPIOB->IDR&0x600)>>9; //entradas PB9 e PB10

		if (i == j) {
			GPIOB->ODR = 0x01;
		} else {
			GPIOB->ODR = 0x00;
		}
	}
}
