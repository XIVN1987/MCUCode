#include <stdio.h>

#include "stm32f4xx.h"

volatile int SysTick_10ms = 0;

void SerialInit(void);

void hw_init(void)
{
	SerialInit();
	
	SysTick_Config(SystemCoreClock / 100);
	
	printf("SystemCoreClock = %d\n\n", SystemCoreClock);
}


void SysTick_Handler(void)
{
	SysTick_10ms++;
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
