/*
 * board.h
 *
 * Created: 5/20/2020 12:52:16 PM
 *  Author: Raafat
 */ 


#ifndef BOARD_H_
#define BOARD_H_

/*
	Single LED	:	PB4
	8-LEDs		:	PA0-7	-> Enable latch PF1 (Active High)
	Buttons		:	PD0-1	-> (Active Low)
	Buzzer		:	PE7		-> (Active Low)
*/

#include "avr/io.h"
#include "data_types.h"
#include "bit_handle.h"

#define BUZ_PORT		PORTE
#define BUZ_DDR			DDRE
#define BUZ_PIN			PE7

#define LED_PORT		PORTB
#define LED_DDR			DDRB
#define LED_PIN			PB4

#define BTN_PORT		PORTD
#define BTN_DDR			DDRD
#define BTN_PINR		PIND
typedef enum{
	BTN0 = 0, BTN1
}Button;
typedef enum{
	IN_STATE_NONE = 0, IN_STATE_PULLUP
}IN_STATE;

#define LEDS_PORT				PORTA
#define LEDS_DDR				DDRA
/*LEDS Enable*/
#define LEDS_ENABLE_PORT		PORTF
#define LEDS_ENABLE_DDR			DDRF
#define LEDS_ENABLE_PIN			PF1


void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Toggle(void);

void Buz_Init(void);
void Buz_On(void);
void Buz_Off(void);
void Buz_Toggle(void);

void Leds_Init(INT8U u8Leds);
void Leds_On(INT8U u8Leds);
void Leds_Off(INT8U u8Leds);
void Leds_Toggle(INT8U u8Leds);

void BTN_Init(Button btn, IN_STATE btnInState);
Bool BTN_IsPressed(Button btn);


#endif /* BOARD_H_ */