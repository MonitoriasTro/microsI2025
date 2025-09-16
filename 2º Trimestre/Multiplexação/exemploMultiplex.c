/*
Implementation of a counter from 0 to 9999
The counter increments every 500ms
The number is displayed in 4 7-segment displays
The displays are multiplexed; each display is active for 5ms, displaying the corresponding digit of the number
The code uses two timers:
- Timer 10: 2Hz, increments the number
- Timer 11: 200Hz, multiplexes the displays

PS: This implementations utilize interruption functions (for TIM10, for example).
    Make sure to check the interruptions slide show on our drive before proceeding
    or implement it without it
*/

#include "stm32f4xx.h"

int number = 0;

void setup();
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
uint32_t convert_to_display(int num);
int get_digit(int num, uint32_t display);

//////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    setup();

    while(1){
        //main loop does nothing, all the work is done in the interrupts
    }
}
//////////////////////////////////////////////////////////////////////////////////

void setup(){
    RCC->AHB1ENR = 0x87;
    GPIOA->MODER = 0x28000400;

    //PB0 a PB3 = saidas (GNDs dos displays)
    GPIOB->MODER = 0x55;
    GPIOB->ODR = ~(0b0001);
    //PC0 a PC6 = saidas (LEDs dos displays)
    GPIOC->MODER = 0x1555;

    //set timer11 to 200Hz
    RCC->APB2ENR |= (1<<18);    //clock timer 11 enable
    TIM11->PSC = 799;
    TIM11->ARR = 99;
    TIM11->CR1 |= 0x01; //enable timer 11 couting
    TIM11->DIER |= 0x01;    //enable timer 11 interuption

    //enable TIM11 interrupt
    NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 5);   //Priority 5
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

    //set timer 10 to 2Hz
    RCC->APB2ENR |= (1<<17);    //clock timer 10 enable
	TIM10->PSC = 7999;
	TIM10->ARR = 999;
	TIM10->CR1 |= 0x01;  //enable timer 10 couting
	TIM10->DIER |= 0x01;  //enable timer 10 interuption

    //enable TIM10 interrupt
	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);    //Priority 2
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

void TIM1_TRG_COM_TIM11_IRQHandler(void){
    //skip to the next display
    if((GPIOB->ODR & 0xF) == (~0b1000 & 0xF))   GPIOB->ODR = ~(0b0001);
    else                        		        GPIOB->ODR = ~(~(GPIOB->ODR) << 1);

    //print digit of the selected display
    GPIOC->ODR = convert_to_display(get_digit(number, GPIOB->ODR & 0xF));

    TIM11->SR &= ~0x01; //clear flag
    TIM11->CNT = 0;     //reset counter
}

void TIM1_UP_TIM10_IRQHandler(void){
    //increment displayed number (each 500ms - this is a 2Hz timer)
    number++;
    if(number>=10000)    number=0;

    //update digit of the selected display
    GPIOC->ODR = convert_to_display(get_digit(number, GPIOB->ODR & 0xF));

    TIM10->SR &= ~0x01; //clear flag
    TIM10->CNT = 0;     //reset counter
}

int get_digit(int num, uint32_t display){
    //this function gets the digit of 'num' corresponding to the active display
    //e.g. if num=1234 and display=0b1101 (2nd display active), it returns 3
    
    switch (display)
    {
    case (0b1110):
        return (num%10)/1;

    case (0b1101):
        return (num%100 - num%10)/10;

    case (0b1011):
        return (num%1000 - num%100)/100;

    case (0b0111):
        return (num%10000 - num%1000)/1000;

    default:
        return 0;
    }
}

uint32_t convert_to_display(int num){
    //this function converts a digit (0-9) to the corresponding 7-segment pins
    //e.g. if num=3, it returns 0b1111001, which lights up segments a,b,c,d and g
    
    switch (num)
    {
    case 0:
        return 0b1111110;

    case 1:
        return 0b0110000;

    case 2:
        return 0b1101101;

    case 3:
        return 0b1111001;

    case 4:
        return 0b0110011;

    case 5:
        return 0b1011011;

    case 6:
        return 0b1011111;

    case 7:
        return 0b1110000;

    case 8:
        return 0b1111111;

    case 9:
        return 0b1111011;

    default:
        return 0;
    }
}
