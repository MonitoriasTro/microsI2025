/* Includes */
#include "stm32g0xx.h"
/*
 * Entradas :
 *    Botão 1 - PC0
 *    Botão 2 - PC1
 * Saidas
 *    LED 1 - PB3
 *    LED 2 - PB4
 *    LED 3 - PB5
 *
 * Tarefa
 *
 * Os leds são ativos em ‘HIGH’ e as chaves ativas em ‘LOW’.
 *
 * Elabore um programa capaz de acionar a quantidade de leds equivalente ao
 * número binário selecionado nas chaves.
 *
 */

uint16_t botoes=0;
uint16_t leds=0;

int main(void)
{

	// Configurando GPIOs

	// ativando clock dos GPIO´s
	 RCC->IOPENR=0x0000003F; //habilita clock das portas

	// Configurando GPIOC como entrada
	GPIOC->MODER=0b0000;
	//           PC1C0

	// Configurando GPIOB como saida
	GPIOB->MODER=0b010101010101;

	//PULL DOWN
	GPIOC->PUPDR=0b1010;

  /* Infinite loop */
  while (1)
  {
	  // Lendo as entradas
	  botoes= (GPIOC->IDR & 0b11);

	  switch(botoes)
	  {
	  case 0b00:
		  leds=0b000;
		  break;
	  case 0b01:
		  leds=0b001;
		  break;
	  case 0b10:
		  leds=0b011;
		  break;
	  case 0b11:
		  leds=0b111;
		  break;
	  }

	  //atualizando saidas
	  GPIOB->ODR=(leds<<3);  //será o valor definido em leds, mas movido para chegar em PB3,PB4 e PB5
  }
}
