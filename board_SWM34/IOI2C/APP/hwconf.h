#ifndef __HWCONF_H__
#define __HWCONF_H__

#include "SWM341.h"


static inline void delayuS(uint16_t us);


static inline void HWconfig(void)
{
	GPIO_Init(GPIOA, PIN1, 1, 1, 0, 1);		// SCL，open-drain output, pull-up
	GPIO_Init(GPIOA, PIN0, 1, 1, 0, 1);		// SDA，open-drain output, pull-up

#define IOI2C_SCL_Low()		GPIO_ClrBit(GPIOA, PIN1); delayuS(2)
#define IOI2C_SCL_High()	GPIO_SetBit(GPIOA, PIN1); delayuS(2)
#define IOI2C_SDA_Low()		GPIO_ClrBit(GPIOA, PIN0); delayuS(2)
#define IOI2C_SDA_High()	GPIO_SetBit(GPIOA, PIN0); delayuS(2)
#define IOI2C_SDA_Value()	GPIO_GetBit(GPIOA, PIN0)

#define IOI2C_SDA_IN()		GPIOA->DIR &= ~(0x01 << PIN0)
#define IOI2C_SDA_OUT()		GPIOA->DIR |=  (0x01 << PIN0)
}


static inline void delayuS(uint16_t us)
{
	uint32_t i = CyclesPerUs * us / 4;
	
	while(i--) __NOP();
}

#endif
