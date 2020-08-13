/*
 * timer.h
 *
 * Created: 6/2/2020 11:21:34 AM
 *  Author: Raafat
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"

#define MODE_NORMAL 0
#define MODE_CTC 1
#define MODE_FAST_PWM 2
#define MODE_PHASE_PWM 3

void Timer0_Init(INT8U mode);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_reset_counters(void);


void Timer0_DelayUS(INT32U delayUS);
void Timer0_DelayMS(INT32U delayMS);

/*duty in range 0:100*/
void Timer0_SetDuty(INT8U duty);
void Timer0_IncDuty(INT8U incduty);
void Timer0_DecDuty(INT8U Decduty);
/*notifyDelay in ms*/
void Timer0_SetNotification(void(*ptrFun)(void), INT32U notifyDelay);


#endif /* TIMER_H_ */