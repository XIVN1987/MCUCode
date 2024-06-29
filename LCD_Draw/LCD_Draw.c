#include <stdint.h>

#include "LCD_Draw.h"


static LCD_t gLCD;


/*******************************************************************************************************************************
* @brief	gLCD init
* @param	width is the width of LCD
* @param	height is the height of LCD
* @param	drawPoint used to draw point
* @param	drawClear used to clear screen
* @param	drawImage used to draw image
* @return
*******************************************************************************************************************************/
void LCD_Draw_Init(uint16_t width, uint16_t height, LCD_DrawPoint_t drawPoint, LCD_DrawClear_t drawClear, LCD_DrawImage_t drawImage)
{
	gLCD.width = width;
	gLCD.height = height;
	gLCD.drawPoint = drawPoint;
	gLCD.drawClear = drawClear;
	gLCD.drawImage = drawImage;
}


/*******************************************************************************************************************************
* @brief	draw point
* @param	x is x of the point
* @param	y is y of the point
* @param	c is color of the point
* @return
*******************************************************************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t c)
{
	gLCD.drawPoint(x, y, c);
}


/*******************************************************************************************************************************
* @brief	clear screen
* @param
* @return
*******************************************************************************************************************************/
void LCD_DrawClear(void)
{
	if(gLCD.drawClear)
	{
		gLCD.drawClear();
	}
	else
	{
		for(uint16_t y = 0; y < gLCD.height; y++)
		{
			for(uint16_t x = 0; x < gLCD.width; x++)
			{
				gLCD.drawPoint(x, y, 0);
			}
		}
	}
}


/*******************************************************************************************************************************
* @brief	draw line
* @param	x0 is x of the start point
* @param	y0 is y of the start point
* @param	x1 is x of the end point
* @param	y1 is y of the end point
* @param	c is color of the line
* @return
*******************************************************************************************************************************/
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t c)
{
	uint16_t i;
	
	if(x0 == x1)		// vertical line
	{
		for(i = 0; i <= y1-y0; i++)	gLCD.drawPoint(x0, y0+i, c);
	}
	else if(y0 == y1)	// horizontal line
	{
		for(i = 0; i <= x1-x0; i++)	gLCD.drawPoint(x0+i, y0, c);
	}
	else
	{
		for(i = 0; i <= x1-x0; i++)	gLCD.drawPoint(x0+i, y0+i*(y1-y0)/(x1-x0), c);
	}
}


/*******************************************************************************************************************************
* @brief	draw rectangle
* @param	x0 is x of the top left point
* @param	y0 is y of the top left point
* @param	x1 is x of the bottom right point
* @param	y1 is y of the bottom right point
* @param	c is color of the rectangle
* @return
*******************************************************************************************************************************/
void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t c)
{
	LCD_DrawLine(x0, y0, x1, y0, c);
	LCD_DrawLine(x1, y0, x1, y1, c);
	LCD_DrawLine(x0, y1, x1, y1, c);
	LCD_DrawLine(x0, y0, x0, y1, c);
}


/*******************************************************************************************************************************
* @brief	draw circle
* @param	Ox is x of the center point
* @param	Oy is y of the center point
* @param	r is radius of the circle
* @param	c is color of the circle
* @return
*******************************************************************************************************************************/
void LCD_DrawCircle(uint16_t Ox, uint16_t Oy, uint16_t r, uint32_t c)
{
	uint16_t vx, vy;						// delta x, delta y
	uint16_t vxmax = (r + (r >> 1)) >> 1;	// vx increases from 0 until the corresponding angle of 45,
											// the value of vx is: r * cos(45/180*3.14) = 0.707r
	for(vx = 0, vy = r; vx <= vxmax; vx++)
	{
		while((vy * vy) > (r * r + 1 - vx * vx)) vy--;
		
		gLCD.drawPoint(Ox+vx, Oy+vy, c);	// quartile 1
		gLCD.drawPoint(Ox+vx, Oy-vy, c);	// quartile 2
		gLCD.drawPoint(Ox-vx, Oy-vy, c); 	// quartile 3
		gLCD.drawPoint(Ox-vx, Oy+vy, c); 	// quartile 4
		
		/* 45-degree mirror image for the other half */ 
		gLCD.drawPoint(Ox+vy, Oy+vx, c);	// quartile 1
		gLCD.drawPoint(Ox+vy, Oy-vx, c);	// quartile 2
		gLCD.drawPoint(Ox-vy, Oy-vx, c); 	// quartile 3
		gLCD.drawPoint(Ox-vy, Oy+vx, c); 	// quartile 4
	}
}


/*******************************************************************************************************************************
* @brief	draw battery icon
* @param	x0 is x of the start point
* @param	y0 is y of the start point
* @param	vol is volume of the battery
* @param	c is color of the battery
* @return
*******************************************************************************************************************************/
void LCD_DrawBattery(uint16_t x0, uint16_t y0, uint16_t vol, uint32_t c)
{
	LCD_DrawRect(x0,   y0,   x0+3, y0+5, c);
	LCD_DrawRect(x0+1, y0+1, x0+2, y0+4, c);
	
	LCD_DrawRect(x0+4, y0-2, x0+21, y0+7, c);
	
	if(vol >= 1)
	{
		LCD_DrawRect(x0+6, y0, x0+7, y0+5, c);
		LCD_DrawRect(x0+8, y0, x0+9, y0+5, c);
		
		if(vol >= 2)
		{
			LCD_DrawRect(x0+11, y0, x0+12, y0+5, c);
			LCD_DrawRect(x0+13, y0, x0+14, y0+5, c);
			
			if(vol >= 3)
			{
				LCD_DrawRect(x0+16, y0, x0+17, y0+5, c);
				LCD_DrawRect(x0+18, y0, x0+19, y0+5, c);
			}
		}	
	}	
}


/*******************************************************************************************************************************
* @brief	draw speaker icon
* @param	x0 is x of the start point
* @param	y0 is y of the start point
* @param	vol is volume of the speaker
* @param	c is color of the speaker
* @return
*******************************************************************************************************************************/
void LCD_DrawSpeaker(uint16_t x0, uint16_t y0, uint16_t off, uint32_t c)
{
	LCD_DrawRect(x0,    y0,   x0+3,  y0+5, c);
	LCD_DrawLine(x0+3,  y0,   x0+11, y0-4, c);
	LCD_DrawLine(x0+3,  y0+5, x0+11, y0+9, c);
	LCD_DrawLine(x0+12, y0-3, x0+12, y0+8, c);
	
	if(off)
		LCD_DrawLine(x0+3, y0-3, x0+15, y0+9, c);
}


/*******************************************************************************************************************************
* @brief	draw segment code
* @param	x0 is x of the start point
* @param	y0 is y of the start point
* @param	val is value to display
* @param	W is width of the segment code
* @param	H is heigth of the segment code
* @param	T is thickness of the segment code
* @param	c is color of the segment code
* @return
*******************************************************************************************************************************/
void LCD_DrawSegment(uint16_t x0, uint16_t y0, uint16_t val, uint16_t W, uint16_t H, uint16_t T, uint32_t c)
{
	uint16_t h = H/2;
	uint8_t SegCode[] = {
		0x3F,	// 0
		0x06,	// 1
		0x5B,	// 2
		0x4F,	// 3
		0x66,	// 4
		0x6D,	// 5
		0x7D,	// 6
		0x07,	// 7
		0x7F,	// 8
		0x6F,	// 9
		0x77,	// A
		0x7C,	// b
		0x39,	// C
		0x5E,	// d
		0x79,	// E
		0x71,	// F
		0x6D,	// S
		0x40,	// -
	};
	
	val = SegCode[val];
	
	if(val & 0x01)		// A
	{
		LCD_DrawLine(x0, y0  , x0+W, y0  , c);
		LCD_DrawLine(x0, y0+1, x0+W, y0+1, c);
		if(T > 2)
		LCD_DrawLine(x0, y0+2, x0+W, y0+2, c);
	}
	
	if(val & 0x02)		// B
	{	
		LCD_DrawLine(x0+W  , y0, x0+W  , y0+h, c);
		LCD_DrawLine(x0+W-1, y0, x0+W-1, y0+h, c);
		if(T > 2)
		LCD_DrawLine(x0+W-2, y0, x0+W-2, y0+h, c);
	}
	
	if(val & 0x04)		// C
	{	
		LCD_DrawLine(x0+W  , y0+h, x0+W  , y0+H, c);
		LCD_DrawLine(x0+W-1, y0+h, x0+W-1, y0+H, c);
		if(T > 2)
		LCD_DrawLine(x0+W-2, y0+h, x0+W-2, y0+H, c);
	}
	
	if(val & 0x08)		// D
	{
		LCD_DrawLine(x0, y0+H  , x0+W, y0+H  , c);
		LCD_DrawLine(x0, y0+H-1, x0+W, y0+H-1, c);
		if(T > 2)
		LCD_DrawLine(x0, y0+H-2, x0+W, y0+H-2, c);
	}
	
	if(val & 0x10)		// E
	{
		LCD_DrawLine(x0  , y0+h, x0  , y0+H, c);
		LCD_DrawLine(x0+1, y0+h, x0+1, y0+H, c);
		if(T > 2)
		LCD_DrawLine(x0+2, y0+h, x0+2, y0+H, c);
	}
	
	if(val & 0x20)		// F
	{
		LCD_DrawLine(x0  , y0, x0  , y0+h, c);
		LCD_DrawLine(x0+1, y0, x0+1, y0+h, c);
		if(T > 2)
		LCD_DrawLine(x0+2, y0, x0+2, y0+h, c);
	}
	
	if(val & 0x40)		// G
	{
		LCD_DrawLine(x0, y0+h-1, x0+W, y0+h-1, c);
		LCD_DrawLine(x0, y0+h  , x0+W, y0+h  , c);
		if(T > 2)
		LCD_DrawLine(x0, y0+h+1, x0+W, y0+h+1, c);
	}
}
