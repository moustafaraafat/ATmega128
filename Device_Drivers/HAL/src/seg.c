/*
* seg.c
*
* Created: 5/21/2020 10:54:27 AM
*  Author: Raafat
*/
#include "seg.h"

static const INT8U numbers[] = {
	NUM_0, NUM_1, NUM_2, NUM_3,
	NUM_4, NUM_5, NUM_6, NUM_7,
	NUM_8, NUM_9, NUM_DOT
};

void Seg_Init(void){
	/*En*/
	setBit(SEG_ENABLE_DDR, SEG_ENABLE_PIN);
	clearBit(SEG_ENABLE_PORT, SEG_ENABLE_PIN);
	/*Out*/
	setAllBits(SEG_DATA_DDR);
	setBits(SEG_DIGIT_DDR, SEG_DIGIT_MSK);
	/*Default*/
	setAllBits(SEG_DATA_PORT);
	clearBits(SEG_DIGIT_PORT, SEG_DIGIT_MSK);

}
/*
u8Digit: (1-4)
u8Value: (1-9, '.')
*/
void Seg_Display(INT8U u8Digit, INT8U u8Value){
	/*Select Digit (Active high)*/
	setBit(SEG_DIGIT_PORT, u8Digit-1);
	/*Apply Data Value	*/
	if(u8Value == NUM_DOT){
		SEG_DATA_PORT = numbers[10];
		}else{
		SEG_DATA_PORT = numbers[u8Value];
	}
	/*Wait for 1 ms*/
	_delay_ms(1);
	/*Un-select digit*/
	clearBit(SEG_DIGIT_PORT, u8Digit-1);
}
void Seg_DiplayInt(INT32U u32IntValue){
	INT8U digit = 4;
	if (0 == u32IntValue){			/*Handling the 0 case*/
		Seg_Display(digit, u32IntValue%10);
		return;
	}
	while(0 != u32IntValue){
		Seg_Display(digit, u32IntValue%10);
		u32IntValue /= 10;
		_delay_ms(10);
		digit--;
	}
}
void Seg_DiplayFloat(FP32 u32FloatValue){
	INT32U a_tmpInt1 = u32FloatValue;                  /* Get the integer part (12)*/
	FP32 a_tmpFrac = u32FloatValue - a_tmpInt1 + 0.00001;      /* Get fraction (0.34)*/
	INT8U a_tmpInt2 = a_tmpFrac * 100;  		/* Turn into integer (34)*/
	Seg_Display(1, a_tmpInt1 / 10);
	Seg_Display(2, a_tmpInt1 % 10);
	Seg_Display(2, NUM_DOT);
	Seg_Display(3, a_tmpInt2 / 10);
	Seg_Display(4, a_tmpInt2 % 10);
	
/*	INT32U a_tmpInt1 = u32FloatValue*100;           
	Seg_DiplayInt(a_tmpInt1);
	Seg_Display(2, NUM_DOT);
*/

}