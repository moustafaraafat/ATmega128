/*
 * spi_eeprom.c
 *
 * Created: 6/7/2020 2:01:20 PM
 *  Author: Raafat
 */ 

#include "spi_eeprom.h"

static void SPI_EEPROM_WriteEnable(void);

void SPI_EEPROM_WriteEnable(void){
	clearBit(SPI_PORT, SPI_SS);
	SPI_Tranceive(INS_WREN);
	setBit(SPI_PORT, SPI_SS);	
	_delay_ms(10);
}

void	SPI_EEPROM_Init(void){
	SPI_Init(MODE_MASTER);
}
INT8U	SPI_EEPROM_ReadByte(INT16U u16RomAddr){
	INT8U result = 0;
	clearBit(SPI_PORT, SPI_SS);

	SPI_Tranceive( INS_READ | ( (u16RomAddr>>5 ) & 0x08 ) );	/*Send instruction*/
	SPI_Tranceive( (INT8U)(u16RomAddr) );		/*Send Address*/
	result = SPI_Tranceive(0x00);
	
	setBit(SPI_PORT, SPI_SS);
	_delay_ms(10);
	return result;
}
void	SPI_EEPROM_WriteByte(INT16U u16RomAddr, INT8U u8Data){
	SPI_EEPROM_WriteEnable();
	clearBit(SPI_PORT, SPI_SS);

	SPI_Tranceive( INS_WRITE | ( (u16RomAddr>>5 ) & 0x08 ) );	/*Send instruction*/
	SPI_Tranceive( (INT8U)(u16RomAddr) );		/*Send Address*/
	SPI_Tranceive(u8Data);
	
	setBit(SPI_PORT, SPI_SS);
	_delay_ms(10);
}