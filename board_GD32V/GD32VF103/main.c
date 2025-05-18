#include "gd32vf103.h"


#define LED_PIN		GPIO_PIN_13
#define LED_PORT	GPIOC
#define LED_PCLK	RCU_GPIOC


int main(void)
{
	SystemInit();

	rcu_periph_clock_enable(LED_PCLK);
	
	gpio_init(LED_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PIN);
	
	while(1)
	{
		GPIO_BC(LED_PORT) = LED_PIN;
		for(int i = 0; i < SystemCoreClock; i++) __asm volatile ("nop");
		GPIO_BOP(LED_PORT) = LED_PIN;
		for(int i = 0; i < SystemCoreClock; i++) __asm volatile ("nop");
	}
}
