#include <stdio.h>

#include "stm32f4xx.h"

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


void SerialInit(void);

int main(void)
{
	uint32_t n = 0;
	
	SerialInit();
	
	SEGGER_RTT_Init();
	
	while(1)
	{
		Value = sines[n++];
		Value2 = sines[(n + 20) % sizeof(sines)];
		if(n == sizeof(sines))
			n = 0;
		
		printf("%d %d, ", Value, Value2);
		
		SEGGER_RTT_printf(0, "%d %d, ", Value, Value2);
		
		for(int i = 0; i < SystemCoreClock/1024; i++) __NOP();
	}
}


void SerialInit(void)
{
	GPIO_InitTypeDef  GPIO_initStruct;
	USART_InitTypeDef USART_initStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_initStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_initStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_initStruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOA, &GPIO_initStruct);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);	// USART1_TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	// USART1_RX
	
	USART_initStruct.USART_BaudRate = 115200;
	USART_initStruct.USART_WordLength = USART_WordLength_8b;
	USART_initStruct.USART_StopBits = USART_StopBits_1;
	USART_initStruct.USART_Parity = USART_Parity_No;
	USART_initStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_initStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_initStruct);
	USART_Cmd(USART1, ENABLE);
}

int fputc(int ch, FILE *f)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, ch);
	
	return ch;
}
