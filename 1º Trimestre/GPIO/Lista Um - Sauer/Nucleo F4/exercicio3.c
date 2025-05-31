#include "stm32f4xx.h"

int main(void) {
    int x = 0, y = 0;
	RCC -> AHB1ENR = 0X87;
	GPIOA -> MODER = 0X28000100;
	GPIOB -> MODER = 0X00;
	GPIOB -> PUPDR = 0XAAAA;
    
    while (1) {
        if ((GPIOB -> IDR &= 0X10) == 0X10) x++;
        if ((GPIOB -> IDR &= 0X20) == 0X20) x = x + 2;
        if ((GPIOB -> IDR &= 0X40) == 0X40) y++;
        if ((GPIOB -> IDR &= 0X80) == 0X80) y = y + 2;
        if (x == y){
            GPIOA -> ODR |= 0X10;
        }
        else {
            GPIOA -> ODR &= 0X00;
        }
        x = 0;
        y = 0;
    }
}