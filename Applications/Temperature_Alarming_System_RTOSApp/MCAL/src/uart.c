/*
* uart.c
*
* Created: 6/3/2020 2:31:48 PM
*  Author: Raafat
*/
#include "uart.h"

static void (*ptrToRecUART0)(void);
static void (*ptrToRecUART1)(void);


void Uart_Init(UART_Type uartNum, INT32U u32Baud){
	INT16U ubrr = ((F_CPU)/(16*u32Baud)) - 1;
	switch(uartNum)
	{
		case UART_0:
		/* Set baud rate */
		UBRR0H = (INT8U)(ubrr>>8);
		UBRR0L = (INT8U)ubrr;
		/* Enable receiver and transmitter */
		UCSR0B = (1<<RXEN)|(1<<TXEN);
		/* Set frame format: 8data, 2stop bit */
		UCSR0C = (3<<UCSZ0);
		break;
		case UART_1:
		/* Set baud rate */
		UBRR1H = (INT8U)(ubrr>>8);
		UBRR1L = (INT8U)ubrr;
		/* Enable receiver and transmitter */
		UCSR1B = (1<<RXEN)|(1<<TXEN);
		/* Set frame format: 8data, 2stop bit */
		UCSR1C = (3<<UCSZ0);
		break;
	}
}
void Uart_SendByte(UART_Type uartNum, INT8U u8Data){
	switch(uartNum)
	{
		case UART_0:
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE)) );
		/* Put data into buffer, sends the data */
		UDR0 = u8Data;
		break;
		case UART_1:
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<UDRE)) );
		/* Put data into buffer, sends the data */
		UDR1 = u8Data;
		break;
	}
}

INT8U Uart_ReceiveByte(UART_Type uartNum){
	INT8U u8Data = 0;
	switch(uartNum)
	{
		case UART_0:
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<RXC)) );
		/* Put data into buffer, sends the data */
		u8Data = UDR0;
		break;
		case UART_1:
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<RXC)) );
		/* Put data into buffer, sends the data */
		u8Data = UDR1;
		break;
	}
	return u8Data;
}
void Uart_SendStr(UART_Type uartNum, INT8U* pu8Str){
	while (*pu8Str)
	{
		Uart_SendByte(uartNum, *pu8Str);
		pu8Str++;
	}
}
Bool Uart_ReceiveByte_Unblock(UART_Type uartNum, INT8U* pu8Data){
	Bool result = FALSE;
	switch(uartNum)
	{
		case UART_0:
		if( ( UCSR0A & (1<<RXC)) ){
			result = TRUE;
			(*pu8Data) = UDR0;
		}
		break;
		case UART_1:
		if( ( UCSR1A & (1<<RXC)) ){
			result = TRUE;
			(*pu8Data) = UDR1;
		}
		break;
	}
	return result;
}
void Uart0_Rec_Int_Enable(void){
	UCSR0B |= 1<< RXCIE0;

}
void Uart1_Rec_Int_Enable(void){
	UCSR1B |= 1<< RXCIE1;

}
void Uart0_Rec_Int_Disable(void){
	UCSR0B &= ~(1<< RXCIE0);
}
void Uart1_Rec_Int_Disable(void){
	UCSR1B &= ~(1<< RXCIE1); 
}
INT8U Uart0_ImmedReceiveByte(void){
	return UDR0;
}
INT8U Uart1_ImmedReceiveByte(void){
	return UDR1;
}
void Uart0_Callback_Rec(void(*ptrFun)(void)){
	ptrToRecUART0 = ptrFun;
}
void Uart1_Callback_Rec(void(*ptrFun)(void)){
	ptrToRecUART1 = ptrFun;
}
ISR(USART0_RX_vect){
	ptrToRecUART0();
}
ISR(USART1_RX_vect){
	ptrToRecUART1();
}