/*
 * seg.h
 *
 * Created: 5/21/2020 10:54:05 AM
 *  Author: Raafat
 */ 


#ifndef SEG_H_
#define SEG_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"
#include "util/delay.h"

#define SEG_DATA_PORT			PORTC
#define SEG_DATA_DDR			DDRC


#define SEG_DIGIT_PORT			PORTA
#define SEG_DIGIT_DDR			DDRA
#define SEG_DIGIT_MSK			0x0F

/*7-Segment Enable (Active Low)*/
#define SEG_ENABLE_PORT			PORTF
#define SEG_ENABLE_DDR			DDRF
#define SEG_ENABLE_PIN			PF2

#define NUM_0					0xC0
#define NUM_1					0xF9
#define NUM_2					0xA4
#define NUM_3					0xB0
#define NUM_4					0x99
#define NUM_5					0x92
#define NUM_6					0x82
#define NUM_7					0xF8
#define NUM_8					0x80
#define NUM_9					0x90
#define NUM_DOT					0x7F
/*
	u8Digit: (1-4)
	u8Value: (1-9, '.')
*/
void Seg_Init(void);
void Seg_Display(INT8U u8Digit, INT8U u8Value);
/*Do it*/
void Seg_DiplayInt(INT32U u32IntValue);
void Seg_DiplayFloat(FP32 u32FloatValue);

#endif /* SEG_H_ */