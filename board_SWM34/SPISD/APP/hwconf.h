#ifndef __HWCONF_H__
#define __HWCONF_H__

#include "SWM341.h"


static inline void SPISD_HW_Init(void)
{
	SPI_InitStructure SPI_initStruct;
	
	PORT_Init(PORTC, PIN7, PORTC_PIN7_SPI1_SCLK, 0);
	PORT_Init(PORTC, PIN6, PORTC_PIN6_SPI1_MOSI, 0);
	PORT_Init(PORTC, PIN5, PORTC_PIN5_SPI1_MISO, 1);
	
	SPI_initStruct.clkDiv = SPI_CLKDIV_512;		// 100KHz-400KHz
	SPI_initStruct.FrameFormat = SPI_FORMAT_SPI;
	SPI_initStruct.SampleEdge = SPI_SECOND_EDGE;
	SPI_initStruct.IdleLevel = SPI_HIGH_LEVEL;
	SPI_initStruct.WordSize = 8;
	SPI_initStruct.Master = 1;
	SPI_initStruct.RXThreshold = 0;
	SPI_initStruct.RXThresholdIEn = 0;
	SPI_initStruct.TXThreshold = 0;
	SPI_initStruct.TXThresholdIEn = 0;
	SPI_initStruct.TXCompleteIEn = 0;
	SPI_Init(SPI1, &SPI_initStruct);
	SPI_Open(SPI1);
	
	GPIO_INIT(GPIOC, PIN4, GPIO_OUTPUT);
#define SPISD_CS_Low()		GPIO_ClrBit(GPIOC, PIN4)
#define SPISD_CS_High()		GPIO_SetBit(GPIOC, PIN4)
}


static inline void SPISD_HighSpeed(void)
{
	SPI1->CTRL &= ~SPI_CTRL_CLKDIV_Msk;
	SPI1->CTRL |= (16 << SPI_CTRL_CLKDIV_Pos);
}


static inline void SPISD_Write(uint8_t data)
{
	SPI_ReadWrite(SPI1, data);
}


static inline uint8_t SPISD_Read(void)
{
	return SPI_ReadWrite(SPI1, 0xFF);
}


static inline void delayuS(uint16_t us)
{
	uint32_t i = CyclesPerUs * us / 4;
	
	while(i--) __NOP();
}

#endif
