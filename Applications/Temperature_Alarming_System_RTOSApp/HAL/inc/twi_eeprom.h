/*
 * twi_eeprom.h
 *
 * Created: 6/10/2020 1:40:51 PM
 *  Author: Raafat
 */ 


#ifndef TWI_EEPROM_H_
#define TWI_EEPROM_H_

#include "TWI.h"

#define EEPROM_SLA	0xA0

void	TWI_EEPROM_Init(void);
INT8U	TWI_EEPROM_ReadByte(INT16U u16RomAddr);
void	TWI_EEPROM_WriteByte(INT16U u16RomAddr, INT8U u8Data);



#endif /* TWI_EEPROM_H_ */