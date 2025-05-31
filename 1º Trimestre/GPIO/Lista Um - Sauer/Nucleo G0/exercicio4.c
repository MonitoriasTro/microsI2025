#include "stm32g0xx.h"

int main(){
	RCC->IOPENR = 0x0000003F;  //habilita o clock de todos os io's
	GPIOB->MODER = 0x00005555; //saidas: PB0 a PB6; entradas: PB7 a PB10
	GPIOB->PUPDR = 0x002A8000; //entradas com pull down interno

	int b = 0, m1 = 0, m2 = 0, m3 = 0; //variaveis pro debounce

	while (1) {
		b = (GPIOB->IDR&0x80)>>7; //entrada PB7

		//DEBOUNCE
		//1. detector de borda de subida
		if (b && !m2) m1 = 1;
		else m1 = 0;

		if (b) m2 = 1;
		else m2 = 0;

		//2. porta xor
		if ((m1 && !m3) || (!m1 && m3)) m3 = 1;
		else m3 = 0;

		//3. ativacao da carga
		if (m3) GPIOB->ODR ^= 0x01; //inverte o valor do registrador
		else GPIOB->ODR = 0x00;
	}
}
