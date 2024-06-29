#include "SWM341.h"

#include "ST7565.h"
#include "LCD_Draw.h"


void SerialInit(void);

int main(void)
{
	SystemInit();
	
	SerialInit();
	
	ST7565_Init();
	
	LCD_Draw_Init(128, 64, (LCD_DrawPoint_t)ST7565_Point, ST7565_Clear, 0);
	
	LCD_DrawClear();
	
	LCD_DrawRect(0, 0, 127, 63, 1);
	LCD_DrawRect(1, 1, 126, 62, 1);
	
	LCD_DrawBattery(100, 10, 2, 1);
	
	LCD_DrawSpeaker(80, 10, 1, 1);
	
	LCD_DrawSegment(20, 25, 9, 20, 30, 3, 1);
	LCD_DrawSegment(50, 25, 7, 20, 30, 3, 1);
	LCD_DrawCircle(82, 53, 1, 1);
	LCD_DrawCircle(82, 53, 2, 1);
	LCD_DrawSegment(95, 35, 6, 16, 20, 2, 1);
   	
	while(1==1)
	{
	}
}


void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTM, PIN0, PORTM_PIN0_UART0_RX, 1);	//GPIOM.0配置为UART0输入引脚
	PORT_Init(PORTM, PIN1, PORTM_PIN1_UART0_TX, 0);	//GPIOM.1配置为UART0输出引脚
 	
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}

/****************************************************************************************************************************************** 
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}
