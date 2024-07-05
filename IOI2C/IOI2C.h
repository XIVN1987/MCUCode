#ifndef __IOI2C_H__
#define __IOI2C_H__


void IOI2C_Init(void);
void IOI2C_Start(void);
void IOI2C_Stop(void);
uint8_t IOI2C_Write(uint8_t data);
uint8_t IOI2C_Read(uint8_t ack);


#endif
