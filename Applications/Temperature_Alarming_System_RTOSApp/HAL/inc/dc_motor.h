/*
 * dc_motor.h
 *
 * Created: 6/3/2020 8:39:59 AM
 *  Author: Raafat
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"
#include	"board.h"

#define MOTOR_PORT		PORTB
#define MOTOR_DDR		DDRB
#define MOTOR_PIN0		PB0
#define MOTOR_PIN1		PB1

typedef enum  {CLK_WISE, ANTI_CLK_WISE, OFF} MOTOR_STATUS;
	
void motor_init(void);
void motor_rotate(MOTOR_STATUS motor_direction);




#endif /* DC_MOTOR_H_ */