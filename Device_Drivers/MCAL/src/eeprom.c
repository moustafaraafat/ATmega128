/*
 * eeprom.c
 *
 * Created: 6/2/2020 11:13:01 AM
 *  Author: Raafat
 */ 
#include "eeprom.h"

void EEPROM_write(INT16U uiAddress, INT8U ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));

	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

INT8U EEPROM_read(INT16U uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}