#include <stdio.h>
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


void SerialInit(void);

char Buffer[128];

int main(void)
{
	uint32_t n = 0;

	SystemInit();

	SerialInit();

	SEGGER_RTT_Init();

	rcu_periph_clock_enable(LED_PCLK);
	
	gpio_init(LED_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PIN);
	
	uint32_t n_1ms = SystemCoreClock / 4000;

	while(1)
	{
		Value = sines[n++];
		Value2 = sines[(n + 20) % sizeof(sines)];
		if(n == sizeof(sines))
			n = 0;
		
		SEGGER_RTT_printf(0, "%d %d, ", Value, Value2);

		if(SEGGER_RTT_HasData(0))
		{
			int nx = SEGGER_RTT_Read(0, Buffer, 128-1);
			Buffer[nx] = '\0';
			printf("%s", Buffer);
		}

		GPIO_BC(LED_PORT) = LED_PIN;
		for(int i = 0; i < n_1ms; i++) __asm volatile ("nop");
		GPIO_BOP(LED_PORT) = LED_PIN;
		for(int i = 0; i < n_1ms; i++) __asm volatile ("nop");
	}
}


void SerialInit(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_USART0);

	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);			// USART0 TX
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);	// USART0 RX

	usart_deinit(USART0);
	usart_baudrate_set(USART0, 115200);
	usart_word_length_set(USART0, USART_WL_8BIT);
	usart_stop_bit_set(USART0, USART_STB_1BIT);
	usart_parity_config(USART0, USART_PM_NONE);
	usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_enable(USART0);
}

int _write(int fd, char *ptr, int len)
{
	for(int i = 0; i < len; i++)
	{
		usart_data_transmit(USART0, *ptr++);

		while(usart_flag_get(USART0, USART_FLAG_TBE)== RESET) {}
	}

	return len;
}
