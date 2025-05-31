#include "stm32g0xx.h"

int main(){
	RCC->IOPENR = 0x0000003F;  //habilita o clock de todos os io's
	GPIOB->MODER = 0x00005555; //saidas: PB0 a PB6; entradas: PB7 a PB10
	GPIOB->PUPDR = 0x002A8000; //entradas com pull down interno

	while (1) {
        //desloca os registradores de entrada 7 bits para a direita
        //(explicação na questão um)
		int i = (GPIOB->IDR&0x780)>>7; 
		switch(i) {
			//caso qualquer uma das combinações possiveis por duas chaves 
			//for feita, ativa o led; observe que, por ser utilizado uma variavel
			//tipo int, podemos fazer nossa logica com numeros decimais
			case 3: 
			case 5:
			case 6:
			case 9:
			case 10:
			case 12:
			case 15:
				GPIOB->ODR = 0x01; //led ligado (PB0)
				break;
			default:
				GPIOB->ODR = 0x00; //led desligado
				break;
		}
	}
}
