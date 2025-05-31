#include "stm32f4xx.h"

int main(void) {    
    RCC -> AHB1ENR = 0X87;
    GPIOA -> MODER = 0X28155500; //A=PA4, B=PA5... G=PA10;
    GPIOB -> MODER = 0X00;
    GPIOB -> PUPDR = 0XAAAA;

    while (1) {
        if ((GPIOB -> IDR &= 0XF0) == 0X00){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X3F0;	//ESCREVER "0"
        }
        if ((GPIOB -> IDR &= 0XF0) == 0X10){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X60;	//ESCREVER "1"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X20){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X5B0;	//ESCREVER "2"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X30){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X4F0;	//ESCREVER "3"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X40){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X660;	//ESCREVER "4"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X50){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X6D0;	//ESCREVER "5"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X60){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X7D0;	//ESCREVER "6"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X70){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X70;	//ESCREVER "7"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X80){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X7F0;	//ESCREVER "8"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0X90){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X6F0;	//ESCREVER "9"
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XA0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X770;	//ESCREVER "A" (10)
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XB0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X7C0;	//ESCREVER "B" (11)
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XC0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X390;	//ESCREVER "C" (12)
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XD0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X5E0;	//ESCREVER "D" (13)
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XE0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X790;	//ESCREVER "E" (14)
        }
        else if ((GPIOB -> IDR &= 0XF0) == 0XF0){
            GPIOA -> ODR &=~ 0x7F0;	//LIMPAR
            GPIOA -> ODR |= 0X710;	//ESCREVER "F" (15)
        }
    }
}