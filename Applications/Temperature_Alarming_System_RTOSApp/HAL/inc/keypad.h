/*
 * keypad.h
 *
 * Created: 5/21/2020 1:01:28 PM
 *  Author: Raafat
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"

#define KEY_PORT		PORTD
#define KEY_DDR			DDRD
#define KEY_PINR		PIND

#define KEY_ROWS_MSK		0x0F
#define KEY_COLS_MSK		0xF0

#define KEY_NONE			0xFF

void Key_Init(void);
INT8U Key_GetKey(void);

#endif /* KEYPAD_H_ */