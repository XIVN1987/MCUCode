#include "FlashOS.h"


struct FlashDevice const FlashDevice  =  {
	FLASH_DRV_VERS,			// Driver Version, do not modify!
	"GD32VF103xB FLASH",	// Device Name
	ONCHIP,					// Device Type
	0x08000000,				// Device Start Address
	0x00020000,				// Device Size in Bytes (128KB)
	0x00000400,				// Programming Page Size (1K)
	0,						// Reserved, must be 0
	0xFF,					// Initial Content of Erased Memory
	1000,					// Program Page Timeout 1000 mSec
	2000,					// Erase Sector Timeout 2000 mSec

// Specify Size and Address of Sectors
	0x0400, 0x000000,		// Sector Size 1KB
	SECTOR_END
};
