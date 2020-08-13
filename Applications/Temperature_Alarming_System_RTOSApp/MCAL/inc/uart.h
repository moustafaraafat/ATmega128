/*
 * uart.h
 *
 * Created: 6/3/2020 2:31:36 PM
 *  Author: Raafat
 */ 


#ifndef UART_H_
#define UART_H_


#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"

typedef enum {
	UART_0 = 0, UART_1
}UART_Type;

void Uart_Init(UART_Type uartNum, INT32U u32Baud);
void Uart_SendByte(UART_Type uartNum, INT8U u8Data);
void Uart_SendStr(UART_Type uartNum, INT8U* pu8Str);
INT8U Uart_ReceiveByte(UART_Type uartNum);
Bool Uart_ReceiveByte_Unblock(UART_Type uartNum, INT8U* pu8Data);

void Uart0_Rec_Int_Enable(void);
void Uart1_Rec_Int_Enable(void);

void Uart0_Rec_Int_Disable(void);
void Uart1_Rec_Int_Disable(void);

INT8U Uart0_ImmedReceiveByte(void);
INT8U Uart1_ImmedReceiveByte(void);

void Uart0_Callback_Rec(void(*ptrFun)(void));
void Uart1_Callback_Rec(void(*ptrFun)(void));




#endif /* UART_H_ */