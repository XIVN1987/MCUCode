#include <stdio.h>

#include "stm32f10x.h"


void SerialInit(void);


int main(void)
{
	GPIO_InitTypeDef GPIO_initStruct;
	
	SerialInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_15;		// KEY
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_initStruct);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_15;		// LED
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_initStruct);
	
	while(1)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_15, GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15) ? Bit_RESET : Bit_SET);
		
		printf("Hi from STM32F103\n");
		
		for(int i = 0; i < SystemCoreClock / 8; i++) __NOP();
	}
}


void SerialInit(void)
{
	GPIO_InitTypeDef  GPIO_initStruct;
	USART_InitTypeDef USART_initStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_9;		// USART1_TX
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initStruct);
	
	GPIO_initStruct.GPIO_Pin = GPIO_Pin_10;		// USART1_RX
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_initStruct);
	
	
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
