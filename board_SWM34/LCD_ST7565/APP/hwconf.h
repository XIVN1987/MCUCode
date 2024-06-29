#ifndef __HWCONF_H__
#define __HWCONF_H__

#include "SWM341.h"


static inline void delayuS(uint16_t us);


static inline void ST7565_HW_Init(void)
{
	SPI_InitStructure SPI_initStruct;
	
	PORT_Init(PORTC, PIN4, PORTC_PIN4_SPI1_SSEL, 0);
	PORT_Init(PORTC, PIN7, PORTC_PIN7_SPI1_SCLK, 0);
	PORT_Init(PORTC, PIN6, PORTC_PIN6_SPI1_MOSI, 0);
	PORT_Init(PORTC, PIN5, PORTC_PIN5_SPI1_MISO, 1);
	
	SPI_initStruct.clkDiv = SPI_CLKDIV_16;
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
	
	GPIO_INIT(GPIOA, PIN12, GPIO_OUTPUT);
#define ST7565_RST_Low()	GPIO_ClrBit(GPIOA, PIN12)
#define ST7565_RST_High()	GPIO_SetBit(GPIOA, PIN12)

	GPIO_INIT(GPIOA, PIN13, GPIO_OUTPUT);
#define ST7565_A0_Low()		GPIO_ClrBit(GPIOA, PIN13)
#define ST7565_A0_High()	GPIO_SetBit(GPIOA, PIN13)

	ST7565_RST_Low();
	delayuS(1000 * 5);
	ST7565_RST_High();
	delayuS(1000 * 5);
}


static inline void ST7565_WrCmd(uint8_t cmd)
{
	ST7565_A0_Low();
	
	SPI_ReadWrite(SPI1, cmd);
}


static inline void ST7565_WrData(uint8_t data)
{
	ST7565_A0_High();
	
	SPI_ReadWrite(SPI1, data);
}


static inline void delayuS(uint16_t us)
{
	uint32_t i = CyclesPerUs * us / 4;
	
	while(i--) __NOP();
}

#endif
