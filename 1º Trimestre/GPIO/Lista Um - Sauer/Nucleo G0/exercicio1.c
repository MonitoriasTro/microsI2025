#include "stm32g0xx.h"

int main(){
	RCC->IOPENR = 0x0000003F;  //habilita o clock de todos os io's
	GPIOB->MODER = 0x00001555; //saidas: PB0 a PB6; entradas: PB7 a PB9
	GPIOB->PUPDR = 0x000A8000; //entradas com pull down interno

	while (1) {
		//desloca os registradores de entrada 7 bits para a direita
		//desta forma, o bit menos significativo sera o PB7, seguido por PB8 e PB9
		//Ex.: caso PB7 esteja ligado, i = 1; caso PB8 esteja ligado, i = 2,
		//caso PB7 e PB8 estejam ligados, i = 3; e assim sucessivamente
		int i = (GPIOB->IDR&0x380)>>7;
		switch (i) {
			case 0:
				GPIOB->ODR = 0x0000; //nenhum led ligado
				break;
			case 1:
				GPIOB->ODR = 0x0001; //primeiro (PB0) led ligado
				break;
			case 2:
				GPIOB->ODR = 0x0003; //primeiro (PB0) e segundo (PB1) led ligados
				break;
			case 3:
				GPIOB->ODR = 0x0007; //primeiro (PB0), segundo (PB1) e terceiro (PB2) led ligados
				break;
			case 4:
				GPIOB->ODR = 0x000F; //...
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
				GPIOB->ODR = 0x0000; //nenhum led ligado
				break;
		}
	}
}
