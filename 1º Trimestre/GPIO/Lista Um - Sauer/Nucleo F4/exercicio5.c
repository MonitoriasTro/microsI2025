#include "stm32f4xx.h"

int main(void) {
    int x = 0;
    RCC -> AHB1ENR = 0X87;
    GPIOA -> MODER = 0X28000100;
    GPIOB -> MODER = 0X00;
    GPIOB -> PUPDR = 0XA00;
    
    while (1) {
        if ((GPIOB -> IDR &= 0X10) == 0X10 && x == 0){	//Se o botão estiver apertado...
            if ((GPIOA -> ODR &= 0X10) == 0X10){		//Se a saída está ligada...
                        GPIOA -> ODR &=~ 0X10;			//Ela desliga.
                    }
            else if ((GPIOA -> ODR &= 0X10) == 0X00){	//Se a saída está desligada...
                GPIOA -> ODR |= 0X10;					//Ela liga.
            }
            x = 1; 										//Quando o botão é apertado, x vai a 1
        }
        if((GPIOB -> IDR &= 0x10) == 0x00) x = 0;		//Se o botão for solto, x vai à zero
    }
}