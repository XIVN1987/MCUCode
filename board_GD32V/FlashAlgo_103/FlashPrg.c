#include "FlashOS.h"
#include "gd32vf103.h"     


/*******************************************************************************************************************************
* @brief	Initialize Flash Programming Functions
* @param	adr is Device Base Address
* @param	clk	is Clock Frequency (Hz)
* @param	fnc	is Function Code (1 - Erase, 2 - Program, 3 - Verify)
* @return	0 - OK,  1 - Failed
*******************************************************************************************************************************/
int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{
	if(fnc == 1)
	{
	}

	return 0;
}


/*******************************************************************************************************************************
* @brief	De-Initialize Flash Programming Functions
* @param	fnc	is Function Code (1 - Erase, 2 - Program, 3 - Verify)
* @return	0 - OK,  1 - Failed
*******************************************************************************************************************************/
int UnInit(unsigned long fnc)
{
	return 0;
}


/*******************************************************************************************************************************
* @brief	Erase Sector in Flash Memory
* @param	adr	is Sector Address
* @return	0 - OK,  1 - Failed
*******************************************************************************************************************************/
int EraseSector(unsigned long adr)
{
	fmc_unlock();

	/* clear all pending flags */
	fmc_flag_clear(FMC_FLAG_END);
	fmc_flag_clear(FMC_FLAG_WPERR);
	fmc_flag_clear(FMC_FLAG_PGERR);

	fmc_page_erase(adr);

	fmc_lock();
	
	return 0;
}


/*******************************************************************************************************************************
* @brief	Program Page in Flash Memory
* @param	adr	is Page Start Address
* @param	sz	is Page Size
* @param	buf	is Page Data
* @return	0 - OK,  1 - Failed
*******************************************************************************************************************************/
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
	fmc_unlock();

	for(int i = 0; i < sz; i += 4)
	{
		/* clear all pending flags */
		fmc_flag_clear(FMC_FLAG_END);
		fmc_flag_clear(FMC_FLAG_WPERR);
		fmc_flag_clear(FMC_FLAG_PGERR);

		fmc_word_program(adr + i, *((uint32_t *)&buf[i]));
	}

	fmc_lock();

	return 0;
}
