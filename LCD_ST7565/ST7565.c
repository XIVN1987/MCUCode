#include "hwconf.h"

#include "ST7565.h"


/*******************************************************************************************************************************
* @brief	LCD based on ST7565R init
* @param
* @return
*******************************************************************************************************************************/
void ST7565_Init(void)
{
	ST7565_HW_Init();
	
	ST7565_WrCmd(ST7565_CMD_RESET);	
	ST7565_WrCmd(ST7565_CMD_POWER_UP);
	ST7565_WrCmd(ST7565_CMD_BIAS_1DIV9);
	ST7565_WrCmd(ST7565_CMD_ADC_NORMAL);
	ST7565_WrCmd(ST7565_CMD_COM_NORMAL);
	ST7565_WrCmd(ST7565_CMD_COM_REVERSE);
	ST7565_WrCmd(ST7565_CMD_V0_RATIO(5));
	ST7565_WrCmd(ST7565_CMD_V0_VOLUME_MODE);
	ST7565_WrCmd(0x51);	//Electronic Volume Register Set, set brightness
	ST7565_WrCmd(ST7565_CMD_START_LINE(0));
	ST7565_WrCmd(ST7565_CMD_DISPLAY_ON);
	
	ST7565_Clear();
}


/*  ST7565 Display Data RAM structure
	bit 0 to 7 of written byte correspond to PyCx-b0..PyCx-b7, column increased by 1 after each write
P0C0-b0   P0C1-b0   P0C2-b0   ...   P0C126-b0   P0C127-b0
P0C0-b1   P0C1-b1   P0C2-b1   ...   P0C126-b1   P0C127-b1
   .         .                ...       .           .
   .         .                ...       .           .
P0C0-b6   P0C1-b6   P0C2-b6   ...   P0C126-b6   P0C127-b6
P0C0-b7   P0C1-b7   P0C2-b7   ...   P0C126-b7   P0C127-b7
   .         .                ...       .           .
   .         .                ...       .           .
   .         .                ...       .           .
P7C0-b0   P7C1-b0   P7C2-b0   ...   P7C126-b0   P7C127-b0
P7C0-b1   P7C1-b1   P7C2-b1   ...   P7C126-b1   P7C127-b1
   .         .                ...       .           .
   .         .                ...       .           .
P7C0-b6   P7C1-b6   P7C2-b6   ...   P7C126-b6   P7C127-b6
P7C0-b7   P7C1-b7   P7C2-b7   ...   P7C126-b7   P7C127-b7
*/
static uint8_t DisplayRAM[8][128] = {0};


/*******************************************************************************************************************************
* @brief	LCD based on ST7565R clear
* @param
* @return
*******************************************************************************************************************************/
void ST7565_Clear(void)
{
	for(uint8_t page = 0; page < 8; page++)
	{
		for(uint8_t column = 0; column < 128; column++)
		{
			DisplayRAM[page][column] = 0;
		}
	}
	
	for(uint8_t page = 0; page < 8; page++)
	{
		ST7565_WrCmd(ST7565_CMD_PAGE_ADDR(page));
		ST7565_WrCmd(ST7565_CMD_COLUMN_UADDR(0));
		ST7565_WrCmd(ST7565_CMD_COLUMN_LADDR(0));
		
		for(uint8_t column = 0; column < 128; column++)
		{
			ST7565_WrData(DisplayRAM[page][column]);
		}
	}
}


/*******************************************************************************************************************************
* @brief	LCD based on ST7565R draw point at (x, y)
* @param	x is horizontal position of the point
* @param	y is vertical position of the point
* @param	v is value of the point
* @return
*******************************************************************************************************************************/
void ST7565_Point(uint8_t x, uint8_t y, uint8_t v)
{
	if((x > 127) || (y > 63)) return;
	
	uint8_t page = y / 8;
	uint8_t nbit = y % 8;
	
	ST7565_WrCmd(ST7565_CMD_PAGE_ADDR(page));
	ST7565_WrCmd(ST7565_CMD_COLUMN_UADDR(x));
	ST7565_WrCmd(ST7565_CMD_COLUMN_LADDR(x));
	
	if(v)
		DisplayRAM[page][x] |= (1 << nbit);
	else
		DisplayRAM[page][x] &=~(1 << nbit);
	
	ST7565_WrData(DisplayRAM[page][x]);
}
