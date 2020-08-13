/*
 * adc.c
 *
 * Created: 5/31/2020 10:59:07 AM
 *  Author: Raafat
 */ 
#include "adc.h"

void ADC_Init(void ){
	/*Clock*/
	ADC_Struct->ADCSRA_BF.ADPS = 0b111;
	/*Ref -> AVcc*/
	ADC_Struct->ADMUX_BF.REFS = 0b01;
	/*Enable*/
	ADC_Struct->ADCSRA_BF.ADEN_B = 1;

}
INT16U ADC_Read(INT8U u8Channel){
	/*Select Channel*/
	ADC_Struct->ADMUX_BF.MUX = u8Channel;
	/*Start Conversion*/
	ADC_Struct->ADCSRA_BF.ADSC_B = 1;
	/*Wait until conversion completes*/
	while(ADC_Struct->ADCSRA_BF.ADSC_B);
	/*Return ADC Data*/
	return ADC_Struct->ADC_DATA;
}