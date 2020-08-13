/*
 * dc_motor.c
 *
 * Created: 6/3/2020 8:40:11 AM
 *  Author: Raafat
 */ 
#include "dc_motor.h"
void motor_init(void)
{
	MOTOR_DDR |= 0x03; 		//make first 2 pins as o/p for L293D
	//PORTC &= 0x02; 		//init with both
}
void motor_rotate(MOTOR_STATUS motor_direction)
{
	switch  (motor_direction)
	{
		case OFF:
		MOTOR_PORT &= ~0x03;  //make it generic
		break;
		case CLK_WISE:
		MOTOR_PORT = (MOTOR_PORT & ~(1<<MOTOR_PIN0)) | (1<<MOTOR_PIN1);
		break;
		case ANTI_CLK_WISE:
		MOTOR_PORT = (MOTOR_PORT & ~(1<<MOTOR_PIN1)) | (1<<MOTOR_PIN0);
		break;
		default:
		break;
	}
}
