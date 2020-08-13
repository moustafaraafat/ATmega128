/*
 * ext_interrupt.h
 *
 * Created: 6/1/2020 2:35:39 PM
 *  Author: Raafat
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"

typedef enum{
	INT_NUM_0 = 0, INT_NUM_1, INT_NUM_2, INT_NUM_3
}INT_NUM;

typedef enum{
	INT_SENSE_FALLING = 2, INT_SENSE_RISING = 3
}INT_SENSE;

void EXT_Enable(INT_NUM intNUM, INT_SENSE intSenseCtrl);
void EXT_Disable(INT_NUM intNUM);
void EXT_CallSetup(INT_NUM intNUM, void(*ptrFun)(void));



#endif /* EXT_INTERRUPT_H_ */