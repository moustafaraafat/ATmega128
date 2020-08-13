/*
 * twi_eeprom.c
 *
 * Created: 6/10/2020 1:41:09 PM
 *  Author: Raafat
 */ 
#include "twi_eeprom.h"


void	TWI_EEPROM_Init(void){
	TWI_Init();
}
INT8U	TWI_EEPROM_ReadByte(INT16U u16RomAddr){
	INT8U u8Data = 0;
	TWI_Start();
	TWI_WriteByte( (EEPROM_SLA) | (INT8U)((u16RomAddr>>7)&0x0E)  , SC_MT_SLA_ACK);
	TWI_WriteByte( (INT8U)(u16RomAddr & 0xFF)  , SC_MT_DATA_ACK);
	TWI_Restart();
	TWI_WriteByte( (EEPROM_SLA) | 0x01  , SC_MR_SLA_ACK);
	TWI_ReadByte(&u8Data, SC_MR_DATA_NOTACK);
	TWI_Stop();
	_delay_ms(10);
	return u8Data;
}
void	TWI_EEPROM_WriteByte(INT16U u16RomAddr, INT8U u8Data){
	TWI_Start();
	TWI_WriteByte( (EEPROM_SLA) | (INT8U)((u16RomAddr>>7)&0x0E)  , SC_MT_SLA_ACK);
	TWI_WriteByte( (INT8U)(u16RomAddr & 0xFF)  , SC_MT_DATA_ACK);
	TWI_WriteByte( u8Data, SC_MT_DATA_ACK);
	TWI_Stop();
	_delay_ms(10);
}