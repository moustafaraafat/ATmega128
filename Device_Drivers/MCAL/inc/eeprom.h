/*
 * eeprom.h
 *
 * Created: 6/2/2020 11:12:29 AM
 *  Author: Raafat
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"

void EEPROM_write(INT16U uiAddress, INT8U ucData);
INT8U EEPROM_read(INT16U uiAddress);


#endif /* EEPROM_H_ */