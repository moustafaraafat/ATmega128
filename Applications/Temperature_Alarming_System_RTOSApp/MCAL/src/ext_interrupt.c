/*
* ext_interrupt.c
*
* Created: 6/1/2020 2:35:52 PM
*  Author: Raafat
*/
#include "ext_interrupt.h"

static void (*callList[4])(void);



void EXT_Enable(INT_NUM intNUM, INT_SENSE intSenseCtrl){
	switch(intNUM)
	{
		case INT_NUM_0:
		switch(intSenseCtrl)
		{
			case INT_SENSE_FALLING:
			clearBit(EICRA, ISC00);
			setBit(EICRA, ISC01);
			break;
			case INT_SENSE_RISING:
			setBit(EICRA, ISC00);
			setBit(EICRA, ISC01);
			break;
		}
		break;
		case INT_NUM_1:
		switch(intSenseCtrl)
		{
			case INT_SENSE_FALLING:
			clearBit(EICRA, ISC10);
			setBit(EICRA, ISC11);
			break;
			case INT_SENSE_RISING:
			setBit(EICRA, ISC10);
			setBit(EICRA, ISC11);
			break;
		}
		break;
		case INT_NUM_2:
		switch(intSenseCtrl)
		{
			case INT_SENSE_FALLING:
			clearBit(EICRA, ISC20);
			setBit(EICRA, ISC21);
			break;
			case INT_SENSE_RISING:
			setBit(EICRA, ISC20);
			setBit(EICRA, ISC21);
			break;
		}
		break;
		case INT_NUM_3:
		switch(intSenseCtrl)
		{
			case INT_SENSE_FALLING:
			clearBit(EICRA, ISC30);
			setBit(EICRA, ISC31);
			break;
			case INT_SENSE_RISING:
			setBit(EICRA, ISC30);
			setBit(EICRA, ISC31);
			break;
		}
		break;
	}
	//EICRA = (EICRA & ~(0x03<<(intNUM*2))) | (intSenseCtrl << (intNUM*2));
	setBit(EIMSK, intNUM);
}
void EXT_Disable(INT_NUM intNUM){
	clearBit(EIMSK, intNUM);
}
void EXT_CallSetup(INT_NUM intNUM, void(*ptrFun)(void)){
	callList[intNUM] = ptrFun;
}

ISR(INT0_vect){
	callList[INT_NUM_0]();
}
ISR(INT1_vect){
	callList[INT_NUM_1]();
}
ISR(INT2_vect){
	callList[INT_NUM_2]();
}
ISR(INT3_vect){
	callList[INT_NUM_3]();
}
