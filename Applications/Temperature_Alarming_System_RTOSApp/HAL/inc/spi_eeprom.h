/*
 * spi_eeprom.h
 *
 * Created: 6/7/2020 2:00:48 PM
 *  Author: Raafat
 */ 


#ifndef SPI_EEPROM_H_
#define SPI_EEPROM_H_

#include "spi.h"

#define		INS_WREN	0x06
#define		INS_READ	0x03
#define		INS_WRITE	0x02

void	SPI_EEPROM_Init(void);
INT8U	SPI_EEPROM_ReadByte(INT16U u16RomAddr);
void	SPI_EEPROM_WriteByte(INT16U u16RomAddr, INT8U u8Data);



#endif /* SPI_EEPROM_H_ */