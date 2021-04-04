#include "stm32f4xx.h"                  // Device header

/*

This programm allows to toggling a led at 1 Hrz

by generating a delay of 1 s

*/

#define GPIOD_CLCK_EN (1<<3)
#define GPIOD_MODE_PIN13 (1<<26)
#define GPIOD_ODR_PIN13 (1<<13)
#define TIMER_CLCK_EN (1<<0)

void Delay_MS(int ms);
void TIMER2_SETUP (void);

int main(void) 

{		
	 RCC->AHB1ENR |= GPIOD_CLCK_EN; 
	 GPIOD->MODER |= GPIOD_MODE_PIN13;
   TIMER2_SETUP ();
	
	while (1)
	
	{		
			Delay_MS(1000);
		  GPIOD->ODR	^= GPIOD_ODR_PIN13;
	    
	}
}

void Delay_MS(int ms)

{
	 TIM2->ARR = (10*ms)-1; // 10000 divided by 10*n 
	 while(!(TIM2->SR & 0x1)) {}
	 TIM2->SR &=~(1<<0);
}


// Timer 2 Config

void TIMER2_SETUP (void)
	
{
	 RCC->APB1ENR |= TIMER_CLCK_EN; // enable clock fro timer 2
	 TIM2->PSC = 1600-1 ; // divide 16000000 by 1600 = 10000
	 TIM2->CR1 = 1;     // enable timer 2
	 TIM2->CNT = 0;    // clear timer counter

}