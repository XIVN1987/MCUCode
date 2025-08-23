#include "ch32v30x.h"


void SerialInit(void);

int main(void)
{
	GPIO_InitTypeDef GPIO_initStruct;

	SerialInit();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_0;		// LED
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_initStruct);

	GPIO_initStruct.GPIO_Pin = GPIO_Pin_2;		// KEY
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_initStruct);
	
	while(1)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0) ? Bit_RESET : Bit_SET);
		
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0)
			printf("Key pressed\n");
		else
			printf("Hi from CH32V307\n");
		
		for(int i = 0; i < SystemCoreClock / 8; i++) __NOP();
	}
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
