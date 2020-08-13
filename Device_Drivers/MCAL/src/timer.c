/*
* timer.c
*
* Created: 6/2/2020 11:21:49 AM
*  Author: Raafat
*/
#include "timer.h"

volatile static INT32U overflows = 0;
volatile static INT32U calcOverflows = 0;
	
static void(* volatile notifier)(void);
volatile static INT32U notifierTime = 0;

void Timer0_Init(INT8U mode){
	Timer0_Stop();
	switch(mode)
	{
		case MODE_NORMAL:
		clearBit(TCCR0, WGM00);
		clearBit(TCCR0, WGM01);
		setBit(TIMSK, TOIE0);
		break;
		case MODE_CTC:
		clearBit(TCCR0, WGM00);
		setBit(TCCR0, WGM01);
		/*Toggle oc0 bin*/
		setBit(TCCR0, COM00);
		clearBit(TCCR0, COM01);
		break;
		case MODE_FAST_PWM:
		setBit(TCCR0, WGM00);
		setBit(TCCR0, WGM01);
		/*Clear OC0 on compare match, set OC0 at BOTTOM*/
		clearBit(TCCR0, COM00);
		setBit(TCCR0, COM01);
		break;
		case MODE_PHASE_PWM:
		setBit(TCCR0, WGM00);
		clearBit(TCCR0, WGM01);
		/*Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting*/
		clearBit(TCCR0, COM00);
		setBit(TCCR0, COM01);
		break;
	}
}
void Timer0_Start(void){
	/*prescaler = 8*/
	clearBit(TCCR0, CS00);
	setBit(TCCR0, CS01);
	clearBit(TCCR0, CS02);
}
void Timer0_Stop(void){
	clearBit(TCCR0, CS00);
	clearBit(TCCR0, CS01);
	clearBit(TCCR0, CS02);
}
void Timer0_reset_counters(void){
	TCNT0 = 0;
	overflows = 0;
}

void Timer0_DelayUS(INT32U delayUS){
	Timer0_reset_counters();
	Timer0_Start();
	while( (delayUS) > (TCNT0 + overflows*256 + 1) );
}
void Timer0_DelayMS(INT32U delayMS){
	Timer0_reset_counters();
	Timer0_Start();
	while( (delayMS*1000UL) > (TCNT0 + overflows*256 + 1) );
}

/*duty in range 0:100*/
void Timer0_SetDuty(INT8U duty){
	OCR0 = (duty*255UL)/100;
}
void Timer0_IncDuty(INT8U incduty){
	if((OCR0 + (incduty*255UL)/100) <= 255){
		OCR0 += (incduty*255UL)/100;
		}else{
		OCR0 = 255;
	}
}
void Timer0_DecDuty(INT8U Decduty){
	if((OCR0 >= (Decduty*255UL)/100) ){
		OCR0 -= (Decduty*255UL)/100;
		}else{
		OCR0 = 0;
	}
}
/*notifyDelay in ms*/ /*Add once or repeated*/
void Timer0_SetNotification(void(*ptrFun)(void), INT32U notifyDelay){
	notifier = ptrFun;
	notifierTime = notifyDelay;
	Timer0_reset_counters();
	Timer0_Start();
	// calculate counter
	TCNT0 = 256 - ((notifyDelay*1000)%256 - 1);
	calcOverflows = (notifyDelay*1000)/256 + 1;
}
/*Do a stop ntification*/
/**/


ISR(TIMER0_OVF_vect){
	overflows++;
	if(overflows == calcOverflows){
		/*notifier();
		overflows = 0;
		TCNT0 = 256 - ((notifierTime*1000)%256 - 1);*/
		Timer0_Stop();
	}
}