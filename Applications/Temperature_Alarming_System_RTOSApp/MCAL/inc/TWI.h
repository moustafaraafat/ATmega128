/*
 * TWI.h
 *
 * Created: 6/8/2020 1:14:09 PM
 *  Author: Raafat
 */ 


#ifndef TWI_H_
#define TWI_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"

/*Control Status Codes*/
#define		SC_START				0x08
#define		SC_RESTART				0x10
/*Master Transmit Status Codes*/
#define		SC_MT_SLA_ACK			0x18
#define		SC_MT_SLA_NOTACK		0x20
#define		SC_MT_DATA_ACK			0x28
#define		SC_MT_DATA_NOTACK		0x30
/*Master Receive Status Codes*/
#define		SC_MR_SLA_ACK			0x40
#define		SC_MR_SLA_NOTACK		0x48
#define		SC_MR_DATA_ACK			0x50
#define		SC_MR_DATA_NOTACK		0x58

/************************************************************************/
/*	                        Functions Prototypes				         */
/************************************************************************/

/*100 KHz*/
void TWI_Init(void);

Bool TWI_Start(void);
Bool TWI_Restart(void);
void TWI_Stop(void);
void TWI_Wait(void);

Bool TWI_WriteByte(INT8U u8Byte, INT8U u8StatusCode);
Bool TWI_ReadByte(INT8U* pu8Byte, INT8U u8StatusCode);


#endif /* TWI_H_ */