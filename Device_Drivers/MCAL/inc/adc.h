/*
 * adc.h
 *
 * Created: 5/31/2020 10:58:52 AM
 *  Author: Raafat
 */ 


#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
/*
	_BFD	->	Bitfield Decl.
	_BF		->	Bitfield.
	_B		->	Bit.
*/
typedef struct{
	INT8U MUX		:5;
	INT8U ADLAR_B	:1;
	INT8U REFS		:2;
	
}ADMUX_BFD;
typedef struct{
	INT8U ADPS		:3;
	INT8U ADIE_B	:1;
	INT8U ADIF_B	:1;
	INT8U ADFR_B	:1;
	INT8U ADSC_B	:1;
	INT8U ADEN_B	:1;	
}ADCSRA_BFD;

typedef struct{
	INT16U		ADC_DATA;
	ADCSRA_BFD	ADCSRA_BF;
	ADMUX_BFD	ADMUX_BF;
}ADC_Struct_BFD;

#define		ADC_Struct		(((volatile ADC_Struct_BFD *)(0x24)))
/*
#define		ADC_DATA_R		(((volatile INT16U *)(0x24)))
#define		ADC_DATA_LR		(((volatile INT8U *)(0x24)))
#define		ADC_DATA_HR		(((volatile INT8U *)(0x25)))

#define		ADMUX_BFR		(((volatile ADMUX_BFD *)(0x27)))
#define		ADCSRA_BFR		(((volatile ADCSRA_BFD *)(0x26)))
*/

void ADC_Init(void );
INT16U ADC_Read(INT8U u8Channel);




#endif /* ADC_H_ */