#include "hwconf.h"

#include "SPISD.h"


struct sd_card_info sd_card_info;


/*******************************************************************************************************************************
* @brief	SD driver by SPI interface, used for card not bigger than 2GB, and block size equal 512 byte
* @param
* @return	init success?
*******************************************************************************************************************************/
bool SPISD_Init(void)
{
	uint8_t para[4] = {0};
	uint8_t resp[5] = {0};
	
	SPISD_HW_Init();
	
	/* set DI and CS high and apply more than 74 clock pulses to SCLK and the card will go ready to accept native commands */
	SPISD_CS_High();
	for(int i = 0; i < 25; i++) SPISD_Write(0xFF);	// delay at least 74 clock
	
	/* send a CMD0 with CS low to reset the card.
	   The card samples CS signal when a CMD0 is received. If the CS signal is low, the card enters SPI mode */
	SPISD_WrCmd(SD_CMD_GO_IDLE, para, resp, 0);
	if((((struct SD_Resp_R1 *)resp)->_0_ == 1) || (((struct SD_Resp_R1 *)resp)->in_idle == 0))
		goto error;
	
	/* in idle state, the card accepts only CMD0, CMD1, ACMD41 and CMD58 */
	do {
		SPISD_WrCmd(SD_CMD_DO_INIT, para, resp, 0);
	} while(((struct SD_Resp_R1 *)resp)->in_idle == 1);
	
	bool ok = SPISD_RdCSD();
	if(!ok)
		goto error;
	
	SPISD_HighSpeed();
	
	SPISD_CS_High();
	return  true;
	
error:
	SPISD_CS_High();
	return false;
}


/*******************************************************************************************************************************
* @brief	send command to sd card
* @param	cmd is command to send
* @param	para is command parameter
* @param	resp is command response
* @param	has_data indicate whether has data phase after command phase
* @return
*******************************************************************************************************************************/
void SPISD_WrCmd(uint8_t cmd, uint8_t para[], uint8_t resp[], bool has_data)
{
	uint8_t tmp;
	uint8_t rlen;
	
	SPISD_CS_Low();
	
	SPISD_Write(0x40 | (cmd & 0x3F));
	for(int i = 3; i >= 0; i--)
		SPISD_Write(para[i]);
	
	SPISD_Write(0x95);		// CRC for CMD0
	
	switch(cmd & 0xC0)
	{
	case SD_R1:
	case SD_R1b: rlen = 1;	break;
	case SD_R2:  rlen = 2;	break;
	case SD_R3:  rlen = 5;	break;
	default:	 rlen = 1;	break;
	}
	
	do {
		tmp = SPISD_Read();
	} while(((struct SD_Resp_R1 *)&tmp)->_0_ == 1);
	
	for(int i = rlen-1; i >= 0; i--)
	{
		resp[i] = tmp;
		if(i > 0)
		{
			tmp = SPISD_Read();
		}
	}
	
	if(!has_data)
	{
		SPISD_CS_High();
	}
}


/*******************************************************************************************************************************
* @brief	write block to sd card
* @param	addr is address write to
* @param	buff used save write data
* @return	write success?
*******************************************************************************************************************************/
bool SPISD_WrBlk(uint32_t addr, const uint8_t buff[])
{
	uint8_t para[4] = {0};
	uint8_t resp[5] = {0};
	
	if(addr > sd_card_info.block_count)
		goto error;
	
	addr = addr * sd_card_info.block_size;	// address in standard SD card is in bytes
	para[3] = addr >>24;
	para[2] = addr >>16;
	para[1] = addr >> 8;
	para[0] = addr&0xFF;
	
	SPISD_WrCmd(SD_CMD_WRIT_BLK, para, resp, 1);
	if(resp[0] != 0x00)
		goto error;
	
	SPISD_Write(0xFE);				// Data Token
	for(int i = 0; i < sd_card_info.block_size; i++)
	{
		SPISD_Write(buff[i]);
	}
	
	SPISD_Write(0x00);				// CRC
	SPISD_Write(0x00);
	
	uint8_t tmp = SPISD_Read();
	if((tmp & 0x1F) != 0x05)		// data not accepted
	{
		goto error;
	}
	
	while(SPISD_Read() == 0x00);	// wait internal flash write
	
	SPISD_CS_High();
	return  true;
	
error:
	SPISD_CS_High();
	return false;								
}


/*******************************************************************************************************************************
* @brief	read block from sd card
* @param	addr is address read from
* @param	buff used save read data
* @return	read success?
*******************************************************************************************************************************/
bool SPISD_RdBlk(uint32_t addr, uint8_t buff[])
{
	uint8_t tmp;
	uint8_t para[4] = {0};
	uint8_t resp[5] = {0};
	
	if(addr > sd_card_info.block_count)
		goto error;
	
	addr = addr * sd_card_info.block_size;	// address in standard SD card is in bytes
	para[3] = addr >>24;
	para[2] = addr >>16;
	para[1] = addr >> 8;
	para[0] = addr&0xFF;
	
	SPISD_WrCmd(SD_CMD_READ_BLK, para, resp, 1);
	if(resp[0] != 0x00)
		goto error;
	
	do {
		tmp = SPISD_Read();
	} while(tmp != 0xFE);			// Data Token
	
	for(int i = 0; i < sd_card_info.block_size; i++)
	{
		buff[i] = SPISD_Read();
	}
	
	SPISD_Read();					// CRC
	SPISD_Read();
	
	SPISD_CS_High();
	return  true;
	
error:
	SPISD_CS_High();
	return false;
}


/*******************************************************************************************************************************
* @brief	read CSD register
* @param
* @return	read success?
*******************************************************************************************************************************/
bool SPISD_RdCSD(void)
{
	uint8_t tmp;
	uint8_t buf[16];
	uint8_t para[4] = {0};
	uint8_t resp[5] = {0};
	
	SPISD_WrCmd(SD_CMD_READ_CSD, para, resp, 1);
	if(resp[0] != 0x00)
		goto error;
	
	do {
		tmp = SPISD_Read();
	} while(tmp != 0xFE);			// Data Token
	
	for(int i = 15; i >= 0; i--)
		buf[i] = SPISD_Read();
	
	SPISD_Read();					// CRC
	SPISD_Read();
	
	uint16_t c_size    = (((struct SD_Reg_CSDv10 *)buf)->size1   << 2) + ((struct SD_Reg_CSDv10 *)buf)->size0;
	uint8_t c_size_mul = (((struct SD_Reg_CSDv10 *)buf)->sz_mul1 << 1) + ((struct SD_Reg_CSDv10 *)buf)->sz_mul0;
	
	sd_card_info.block_size = 1 << ((struct SD_Reg_CSDv10 *)buf)->sz_blk;
	sd_card_info.block_count = c_size * (1 << (c_size_mul + 2));
	
	SPISD_CS_High();
	return  true;
	
error:
	SPISD_CS_High();
	return false;
}
