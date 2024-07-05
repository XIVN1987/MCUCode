#include "hwconf.h"

#include "IOI2C.h"


/*******************************************************************************************************************************
* @brief	IOI2C init
* @param
* @return
*******************************************************************************************************************************/
void IOI2C_Init(void)
{
	IOI2C_HW_Init();
	
	IOI2C_SDA_High();
	IOI2C_SCL_High();
}


/*******************************************************************************************************************************
* @brief	generate start
* @param
* @return
*******************************************************************************************************************************/
void IOI2C_Start(void)
{
	IOI2C_SCL_Low();
	IOI2C_SDA_High();
	
	IOI2C_SCL_High();
	IOI2C_SDA_Low();	// when SCL high, falling edge on SDA generate start signal
}


/*******************************************************************************************************************************
* @brief	generate stop
* @param
* @return
*******************************************************************************************************************************/
void IOI2C_Stop(void)
{
	IOI2C_SCL_Low();
	IOI2C_SDA_Low();
	
	IOI2C_SCL_High();
	IOI2C_SDA_High();	// when SCL high, rising edge on SDA generate stop signal
}


/*******************************************************************************************************************************
* @brief	IOI2C write
* @param	data to write
* @return	1 ACK received, 0 NAK received
*******************************************************************************************************************************/
uint8_t IOI2C_Write(uint8_t data)
{
	for(int i = 0; i < 8; i++)
	{
		IOI2C_SCL_Low();
		if(data & (1 << (7 - i)))
		{
			IOI2C_SDA_High();
		}
		else
		{
			IOI2C_SDA_Low();
		}
		
		IOI2C_SCL_High();
	}
	
	IOI2C_SDA_IN();
	
	IOI2C_SCL_Low();
	IOI2C_SCL_High();
	uint8_t ack = (IOI2C_SDA_Value() == 0) ? 1 : 0;
	
	IOI2C_SDA_OUT();
	
	return ack;
}


/*******************************************************************************************************************************
* @brief	IOI2C read
* @param	after recv data, 1 send ACK, 0 send NAK
* @return	data received
*******************************************************************************************************************************/
uint8_t IOI2C_Read(uint8_t ack)
{
	uint8_t data = 0;

	IOI2C_SDA_IN();
	
	for(int i = 0; i < 8; i++)
	{
		IOI2C_SCL_Low();
		
		IOI2C_SCL_High();
		data = (data << 1) | IOI2C_SDA_Value();
	}
	
	IOI2C_SDA_OUT();
	
	IOI2C_SCL_Low();
	if(ack)
	{
		IOI2C_SDA_Low();
	}
	else
	{
		IOI2C_SDA_High();
	}
	IOI2C_SCL_High();
	
	return data;
}
