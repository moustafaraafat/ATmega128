/*
 * lcd.h
 *
 * Created: 5/29/2020 3:20:29 AM
 *  Author: Raafat
 */ 


#ifndef LCD_H_
#define LCD_H_


#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"

#define LCD_BiT_MODE 8
/*Define UPPER_4_BITS to use the upper 4 bits, OR don't define it to use lower bits */
#if (4 ==  LCD_BiT_MODE)
//#define LCD_UPPER_4_BITS		/*or remove it for lower*/
#endif

#define LCD_DATA_PORT		PORTC
#define LCD_DATA_DDR		DDRC

#define LCD_CTRL_PORT		PORTB
#define LCD_CTRL_DDR		DDRB

#define	LCD_RS				PB5
#define	LCD_RW				PB6
#define	LCD_EN				PB7
/*Back Light (BL)*/
#define	LCD_BL_PORT			PORTE
#define	LCD_BL_DDR			DDRE
#define	LCD_BL_PIN			PE4

#define CMD_CLEAR			0x01
#define CMD_ENTRY_MODE		0x06
#define CMD_DISP_ON			0x0C
#define CMD_CFG_8_BIT		0x38
#define CMD_CFG_4_BIT_1		0x02
#define CMD_CFG_4_BIT_2		0x28
#define	CMD_INITIALIZE_CHIP	0x30

/* x (1-2 line), y (1-16) cols */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(INT8U u8Char);
void LCD_DispStr(INT8U* pu8Str);
void LCD_DispCharXY(INT8U x, INT8U y, INT8U u8Char);
void LCD_DispStrXY(INT8U x, INT8U y, INT8U* pu8Str);
void LCD_DispInt(int intNum);
void LCD_DispIntXY(INT8U x, INT8U y, int intNum);
void LCD_displayRealNumber(double  Number );
void LCD_displayRealNumberXY(INT8U x, INT8U y, double  Number );

#endif /* LCD_H_ */