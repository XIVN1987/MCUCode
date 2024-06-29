#ifndef __LCD_DRAW_H__
#define __LCD_DRAW_H__


typedef void (*LCD_DrawClear_t)(void);
typedef void (*LCD_DrawPoint_t)(uint16_t x, uint16_t y, uint32_t v);
typedef void (*LCD_DrawImage_t)(uint16_t x, uint16_t y, uint16_t w, uint16_t h, void *image);

typedef struct {
	uint16_t width;
	uint16_t height;
	LCD_DrawPoint_t drawPoint;
	LCD_DrawClear_t drawClear;	// Optional
	LCD_DrawImage_t drawImage;	// Optional
} LCD_t;


void LCD_Draw_Init(uint16_t width, uint16_t height, LCD_DrawPoint_t drawPoint, LCD_DrawClear_t drawClear, LCD_DrawImage_t drawImage);

void LCD_DrawClear(void);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t c);
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t v);
void LCD_DrawRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t v);
void LCD_DrawCircle(uint16_t Ox, uint16_t Oy, uint16_t r, uint32_t c);

void LCD_DrawBattery(uint16_t x0, uint16_t y0, uint16_t vol, uint32_t c);
void LCD_DrawSpeaker(uint16_t x0, uint16_t y0, uint16_t off, uint32_t c);
void LCD_DrawSegment(uint16_t x0, uint16_t y0, uint16_t val, uint16_t W, uint16_t H, uint16_t T, uint32_t c);


#endif
