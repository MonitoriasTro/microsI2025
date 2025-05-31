#include "stm32f4xx.h"

int main(void) {
	RCC -> AHB1ENR = 0X87;
	GPIOA -> MODER |= 0X28155500;
	GPIOB -> MODER |= 0X00;
	GPIOB -> PUPDR |= 0X000AAAAA;
	
    while (1)
	{
		if ((GPIOB -> IDR & 0X70) == 0x00){
			GPIOA -> ODR &= 0X000;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0010){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X0010;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0020){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X0030;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0030){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X0070;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0040){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X00F0;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0050){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X01F0;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0060){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X03F0;
		}
		if ((GPIOB -> IDR & 0X0070) == 0X0070){
			GPIOA -> ODR &= 0X000;
			GPIOA -> ODR |= 0X07F0;
		}
	}
}
