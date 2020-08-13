/*
* board.c
*
* Created: 5/20/2020 12:52:34 PM
*  Author: Raafat
*/
#include "board.h"

void Led_Init(void){
	/*Out*/
	setBit(LED_DDR, LED_PIN);
	/*Off*/
	Led_Off();
}
void Led_On(void){
	/*High*/
	setBit(LED_PORT, LED_PIN);
}
void Led_Off(void){
	/*Low*/
	clearBit(LED_PORT, LED_PIN);
}
void Led_Toggle(void){
	/*Toggle*/
	toggleBit(LED_PORT, LED_PIN);
}

void Buz_Init(void){
	/*Out*/
	setBit(BUZ_DDR, BUZ_PIN);
	/*Off*/
	Buz_Off();
}
void Buz_On(void){
	setBit(BUZ_PORT, BUZ_PIN);
}
void Buz_Off(void){
	clearBit(BUZ_PORT, BUZ_PIN);
}
void Buz_Toggle(void){
	toggleBit(BUZ_PORT, BUZ_PIN);
}
void Leds_Init(INT8U u8Leds){
	/*En*/
	setBit(LEDS_ENABLE_DDR, LEDS_ENABLE_PIN);
	setBit(LEDS_ENABLE_PORT, LEDS_ENABLE_PIN);
	/*Out*/
	setBits(LEDS_DDR, u8Leds);
	/*Off*/
	Leds_Off(u8Leds);
}
void Leds_On(INT8U u8Leds){
	setBits(LEDS_PORT, u8Leds);
}
void Leds_Off(INT8U u8Leds){
	clearBits(LEDS_PORT, u8Leds);
}
void Leds_Toggle(INT8U u8Leds){
	toggleBits(LEDS_PORT, u8Leds);
}
void BTN_Init(Button btn, IN_STATE btnInState){
	/*Input*/
	clearBit(BTN_DDR, btn);
	/*Activate Pullup*/
	switch(btnInState)
	{
		case IN_STATE_NONE:
		clearBit(BTN_PORT, btn);
		break;
		case IN_STATE_PULLUP:
		setBit(BTN_PORT, btn);
		break;
		default:
		break;
	}
}
Bool BTN_IsPressed(Button btn){
	return (!readBit(BTN_PINR, btn));
}