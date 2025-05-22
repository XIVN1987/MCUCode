#include "gd32vf103.h"

#include "SEGGER_RTT.h"


int8_t sines[100] = {
	  0,    6,   12,   18,   24,   30,   36,   42,   48,   53,   58,
	 63,   68,   72,   77,   80,   84,   87,   90,   92,   95,   96,
	 98,   99,   99,  100,   99,   99,   98,   96,   95,   92,   90,
	 87,   84,   80,   77,   72,   68,   63,   58,   53,   48,   42,
	 36,   30,   24,   18,   12,    6,    0,   -6,  -12,  -18,  -24,
	-30,  -36,  -42,  -48,  -53,  -58,  -63,  -68,  -72,  -77,  -80,
	-84,  -87,  -90,  -92,  -95,  -96,  -98,  -99,  -99, -100,  -99,
	-99,  -98,  -96,  -95,  -92,  -90,  -87,  -84,  -80,  -77,  -72,
	-68,  -63,  -58,  -53,  -48,  -42,  -36,  -30,  -24,  -18,  -12,
	 -6
};

volatile int8_t Value;		

volatile int8_t Value2;


#define LED_PIN		GPIO_PIN_13
#define LED_PORT	GPIOC
#define LED_PCLK	RCU_GPIOC


int main(void)
{
	uint32_t n = 0;

	SystemInit();

	SEGGER_RTT_Init();

	rcu_periph_clock_enable(LED_PCLK);
	
	gpio_init(LED_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PIN);
	
	while(1)
	{
		Value = sines[n++];
		Value2 = sines[(n + 20) % sizeof(sines)];
		if(n == sizeof(sines))
			n = 0;
		
		SEGGER_RTT_printf(0, "%d %d, ", Value, Value2);

		GPIO_BC(LED_PORT) = LED_PIN;
		for(int i = 0; i < SystemCoreClock/16; i++) __asm volatile ("nop");
		GPIO_BOP(LED_PORT) = LED_PIN;
		for(int i = 0; i < SystemCoreClock/16; i++) __asm volatile ("nop");
	}
}
