#ifndef __SPISD_H__
#define __SPISD_H__


struct sd_card_info
{
	uint32_t card_type;
	uint32_t block_size;
	uint32_t block_count;
};


bool SPISD_Init(void);
bool SPISD_RdBlk(uint32_t addr, uint8_t buff[]);
bool SPISD_WrBlk(uint32_t addr, const uint8_t buff[]);
void SPISD_WrCmd(uint8_t cmd, uint8_t para[], uint8_t resp[], bool has_data);

bool SPISD_RdCSD(void);



#define SD_R1				(0 << 6)
#define SD_R1b				(1 << 6)
#define SD_R2				(2 << 6)
#define SD_R3				(3 << 6)

#define SD_CMD(cmd, r)		(cmd | r)

#define SD_CMD_GO_IDLE 		SD_CMD( 0, SD_R1)	// card reset
#define SD_CMD_DO_INIT		SD_CMD( 1, SD_R1)	// SEND_OP_COND
#define SD_CMD_READ_CSD		SD_CMD( 9, SD_R1)	// Card Specific Data
#define SD_CMD_READ_CID		SD_CMD(10, SD_R1)	// Card identification number
#define SD_CMD_READ_OCR		SD_CMD(58, SD_R3)	// Operation conditions register
#define SD_CMD_READ_STAT	SD_CMD(13, SD_R2)	// SEND_STATUS
#define SD_CMD_STOP_RD		SD_CMD(12, SD_R1b)	// STOP_TRANSMISSION
#define SD_CMD_READ_BLK		SD_CMD(17, SD_R1)	// READ_SINGLE_BLOCK
#define SD_CMD_READ_BLKs	SD_CMD(18, SD_R1)	// READ_MULTIPLE_BLOCK
#define SD_CMD_WRIT_BLK		SD_CMD(24, SD_R1)	// WRITE_SINGLE_BLOCK
#define SD_CMD_WRIT_BLKs	SD_CMD(25, SD_R1)	// WRITE_MULTIPLE_BLOCK



struct SD_Resp_R1
{
	uint8_t in_idle	  : 1;		// card is in idle state and running the initializing process
	uint8_t erase_rst : 1;		// erase sequence was cleared before executing
	uint8_t illgl_cmd : 1;		// illegal command code was detected
	uint8_t err_crc	  : 1;		// CRC check of the last command failed
	uint8_t err_erase : 1;		// error in the sequence of erase commands occurred
	uint8_t err_addr  : 1;		// misaligned address that did not match the block length was detected
	uint8_t err_para  : 1;		// argument (e.g. address, block length) was outside the allowed range
	uint8_t _0_		  : 1;		// always be 0
};

struct SD_Resp_R2				// response for CMD13(SEND_STATUS)
{
	struct SD_Resp_R1 r1;

	uint8_t out_range : 1;		// out of range
	uint8_t err_erase : 1;		// invalid selection for erase, sectors or groups
	uint8_t wp_violat : 1;		// write protect violation
	uint8_t err_ecc	  : 1;		// Card internal ECC was applied but failed to correct the data
	uint8_t err_icc	  : 1;		// internal card controller error
	uint8_t err_other : 1;		// general or an unknown error occurred during the operation
	uint8_t err_pwd	  : 1;		// sequence or password errors during card lock/unlock operation
	uint8_t locked	  : 1;		// the card is locked by the user
};

struct SD_Resp_R3				// response for CMD58(READ_OCR)
{
	struct SD_Resp_R1 r1;

	uint32_t OCR;
};


struct SD_Reg_OCR
{
	uint16_t		:15;
	uint16_t v2_7	: 1;		// support 2.7v-2.8v
	uint8_t  v2_8	: 1;		// support 2.8v-2.9v
	uint8_t  v2_9	: 1;		// support 2.9v-3.0v
	uint8_t  v3_0	: 1;		// support 3.0v-3.1v
	uint8_t  v3_1	: 1;		// support 3.1v-3.2v
	uint8_t  v3_2	: 1;		// support 3.2v-3.3v
	uint8_t  v3_3	: 1;		// support 3.3v-3.4v
	uint8_t  v3_4	: 1;		// support 3.4v-3.5v
	uint8_t  v3_5	: 1;		// support 3.5v-3.6v
	uint8_t			: 6;
	uint8_t  hicap	: 1;		// high capacity (> 2GB)
	uint8_t  pwup	: 1;		// power-up done
};

struct SD_Reg_CID
{
	uint8_t  _1_	: 1;		// always be 1
	uint8_t  crc7	: 7;		// checksum of the CID contents
	uint16_t date	:12;		// manufacturing date, [0:3] is month, [4:11] is year
	uint16_t 		: 4;
	uint8_t  serial[4];			// serial number
	uint8_t  revision;			// product revision, BCD code
	uint8_t  name[5];			// product name, 5-character ASCII string
	uint16_t oem;				// the card oem (original equipment manufacturer)
	uint8_t  vendor;			// the card manufacturer
};

struct SD_Reg_CSDv10			// CSD version 1.0, used for card not larger than 2GB
{
	uint8_t  _1_	: 1;		// always be 1
	uint8_t  crc7	: 7;		// checksum of the CSD contents

	uint8_t 		: 2;
	uint8_t			: 2;		// file format 
	uint8_t			: 1;		// temporary write protection
	uint8_t			: 1;		// permanent write protection
	uint8_t			: 1;		// copy flag
	uint8_t			: 1;		// file format group 

	uint16_t		: 5;
	uint16_t		: 1;		// partial blocks for write allowed
	uint16_t		: 4;		// max. write data block length
	uint16_t		: 3;		// write speed factor
	uint16_t		: 2;
	uint16_t		: 1;		// write protect group enable 

	uint16_t 		: 7;		// write protect group size
	uint16_t		: 7;		// erase sector size
	uint16_t		: 1;		// erase single block enable
	uint16_t sz_mul0: 1;		// device size multiplier[0]

	uint16_t sz_mul1: 2;		// device size multiplier[2..1]
	uint16_t		: 3;		// max. write current @VDD max 
	uint16_t		: 3;		// max. write current @VDD min
	uint16_t		: 3;		// max. read current @VDD max 
	uint16_t		: 3;		// max. read current @VDD min
	uint16_t size0	: 2;		// device size[1..0]
	
	uint16_t size1	:10;		// device size[11..2], card capacity = ((size1 << 2) + size0) * pow(2, (((sz_mul1 << 1) + sz_mul0) + 2)) * pow(2, BLK_LEN)
	uint16_t		: 2;
	uint16_t		: 1;		// DSR implemented?
	uint16_t		: 1;		// read block misalignment 
	uint16_t		: 1;		// write block misalignment
	uint16_t		: 1;		// partial blocks for read allowed, always be 1

	uint16_t sz_blk : 4;		// max. read data block length, =9 2**9=512B, =10 1024B, =11 2048B
	uint16_t		:12;		// card command classes supported

	uint8_t speed;				// max. data transfer rate 
	uint8_t nsac;				// data read access-time-2 in CLK cycles
	uint8_t taac;				// data read access-time-1

	uint8_t			: 6;
	uint8_t version	: 2;		//CSD structure Version, =0 CSD Version 1.0, =1 CSD Version 2.0
};

#endif
