#include <stdio.h>

#include "ch32v30x.h"


void SerialInit(void);

void hw_init(void)
{
	SystemInit();
	
	SerialInit();

	SysTick->CNT = 0;
	SysTick->CTLR = 1;	// 以 HCLK / 8 为时基

	printf("SystemCoreClock = %d\n\n", SystemCoreClock);
}


uint32_t SysTick_10ms(void)
{
	return SysTick->CNT * 100ull / (SystemCoreClock / 8);
}


void SerialInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);              // PA9  => USART1_TX

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);              // PA10 => USART1_RX

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

int _write(int fd, char *buf, int size)
{
	for(int i = 0; i < size; i++)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) __NOP();
		USART_SendData(USART1, *buf++);
	}

	return size;
}

#include <stddef.h>

void *_sbrk(ptrdiff_t incr)
{
	extern char _end[];
	extern char _heap_end[];
	static char *curbrk = _end;

	if((curbrk + incr < _end) || (curbrk + incr > _heap_end))
		return NULL - 1;

	curbrk += incr;
	
	return curbrk - incr;
}
