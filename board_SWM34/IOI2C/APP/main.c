#include "SWM341.h"

#include "IOI2C.h"


#define SLV_ADDR  0x50	// AT24C02

#define MEM_ADDR  0x10


void SerialInit(void);

uint8_t txbuf[4] = {0x37, 0x55, 0xAA, 0x78};
uint8_t rxbuf[4] = {0};

int main(void)
{
	int i;
	uint8_t ack;
	
	SystemInit();
	
	SerialInit();
	
	IOI2C_Init();
   	
	while(1==1)
	{
		/* write EEPROM*/
		IOI2C_Start();
		
		ack = IOI2C_Write((SLV_ADDR << 1) | 0);
		if(!ack)
		{
			printf("Slave send NAK for address\r\n");
			goto fail;
		}
		
		ack = IOI2C_Write(MEM_ADDR);
		if(!ack)
		{
			printf("Slave send NAK for memory address\r\n");
			goto fail;
		}
		
		for(i = 0; i < 4; i++)
		{
			ack = IOI2C_Write(txbuf[i]);
			if(!ack)
			{
				printf("Slave send NAK for data\r\n");
				goto fail;
			}
		}
		
		IOI2C_Stop();
		
		for(i = 0; i < CyclesPerUs*5000; i++) __NOP();	// Self-timed Write Cycle (5 ms max)
		
		printf("I2C Write %X %X %X %X to EEPROM @ %X\r\n", txbuf[0], txbuf[1], txbuf[2], txbuf[3], MEM_ADDR);
		
		
		/* read EEPROM */
		IOI2C_Start();
		
		ack = IOI2C_Write((SLV_ADDR << 1) | 0);
		if(!ack)
		{
			printf("Slave send NAK for address\r\n");
			goto fail;
		}
		
		ack = IOI2C_Write(MEM_ADDR);
		if(!ack)
		{
			printf("Slave send NAK for memory address\r\n");
			goto fail;
		}
		
		IOI2C_Start();		// ReStart
		
		ack = IOI2C_Write((SLV_ADDR << 1) | 1);
		if(!ack)
		{
			printf("Slave send NAK for address\r\n");
			goto fail;
		}
		
		for(i = 0; i < 3; i++)
		{
			rxbuf[i] = IOI2C_Read(1);
		}
		rxbuf[i] = IOI2C_Read(0);
		
		printf("I2C Read %X %X %X %X from EEPROM @ %X\r\n", rxbuf[0], rxbuf[1], rxbuf[2], rxbuf[3], MEM_ADDR);
		
		if((rxbuf[0] == txbuf[0]) && (rxbuf[1] == txbuf[1]) && (rxbuf[2] == txbuf[2]) && (rxbuf[3] == txbuf[3]))
			printf("Success\r\n");
		else
			printf("Fail\r\n");

fail:
		IOI2C_Stop();
		
		for(int i = 0; i < SystemCoreClock/4; i++) __NOP();
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
