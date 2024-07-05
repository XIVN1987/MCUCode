#ifndef __ST7565_H__
#define	__ST7565_H__


#define ST7565_CMD_RESET				0xE2
#define ST7565_CMD_DISPLAY_ON			0xAF
#define ST7565_CMD_DISPLAY_OFF			0xAE
#define ST7565_CMD_DISPLAY_NORMAL		0xA6
#define ST7565_CMD_DISPLAY_REVERSE		0xA7
#define ST7565_CMD_DISPLAY_ALL_ON		0xA5	// display all points ON
#define ST7565_CMD_DISPLAY_ALL_OFF		0xA4
#define ST7565_CMD_BIAS_1DIV9			0xA2
#define ST7565_CMD_BIAS_1DIV7			0xA3
#define ST7565_CMD_ADC_NORMAL			0xA0	// column address     n <-> SEG n
#define ST7565_CMD_ADC_REVERSE			0xA1	// column address 131-n <-> SEG n
#define ST7565_CMD_COM_NORMAL			0xC0	// COM output normal, COM0 -> COM63
#define ST7565_CMD_COM_REVERSE			0xC8	// COM output reverse, COM63 -> COM0
#define ST7565_CMD_POWER_UP				0x2F
#define ST7565_CMD_V0_VOLUME_MODE		0x81	// adjust brightness by changing V0, must be followed by
												// 'Electronic Volume Register Set', and then exit from this mode
#define ST7565_CMD_V0_RATIO(ratio)		(0x20 | (ratio& 0x07))	// V0 voltage regulator internal resistor ratio
#define ST7565_CMD_START_LINE(line)		(0x40 | (line & 0x3F))	// specify display start line address of the display data RAM
#define ST7565_CMD_PAGE_ADDR(page)		(0xB0 | (page & 0x0F))
#define ST7565_CMD_COLUMN_UADDR(column)	(0x10 | (column >> 4))	// column address upper bit
#define ST7565_CMD_COLUMN_LADDR(column)	(0x00 | (column&0x0F))	// column address lower bit



void ST7565_Init(void);
void ST7565_Clear(void);
void ST7565_Point(uint8_t x, uint8_t y, uint8_t v);


#endif
