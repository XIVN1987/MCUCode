#include <stdio.h>
#include "gd32vw55x.h"


#define LED_PIN		GPIO_PIN_13
#define LED_PORT	GPIOC
#define LED_PCLK	RCU_GPIOC


void SerialInit(void);

int main(void)
{
	SerialInit();

	rcu_periph_clock_enable(LED_PCLK);
	
	gpio_mode_set(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
	
	int delay_cycles = SystemCoreClock / 256;

	while(1)
	{
		printf("Hi from GD32VW553\n");

		gpio_bit_set(LED_PORT, LED_PIN);
		for(int i = 0; i < delay_cycles; i++) __NOP();
		gpio_bit_reset(LED_PORT, LED_PIN);
		for(int i = 0; i < delay_cycles; i++) __NOP();
	}
}


void SerialInit(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_USART0);

	gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);		// USART0 TX

	gpio_af_set(GPIOA, GPIO_AF_8, GPIO_PIN_10);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);	// USART0 RX

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
