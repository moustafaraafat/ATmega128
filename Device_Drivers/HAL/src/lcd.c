/*
* lcd.c
*
* Created: 5/29/2020 3:20:47 AM
*  Author: Raafat
*/
#include "lcd.h"

static void LCD_SendCmd(INT8U u8Cmd);
static void LCD_SendData(INT8U u8Data);
static void LCD_GotoXY(INT8U x, INT8U y);

static void LCD_SendCmd(INT8U u8Cmd){
	#if (8 ==  LCD_BiT_MODE)
	clearBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 0 */
	LCD_DATA_PORT = u8Cmd;				/* upload  u8Cmd*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	
	
	#elif (4 ==  LCD_BiT_MODE)
	#ifdef LCD_UPPER_4_BITS
	clearBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 0 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8Cmd & 0xF0);	/*Send the upper nibble first*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8Cmd & 0x0F) << 4);	/*Send the lower nibble second*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	#else
	clearBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 0 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8Cmd & 0xF0) >> 4);	/*Send the upper nibble first*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8Cmd & 0x0F);	/*Send the lower nibble second*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	#endif
	#endif
}
static void LCD_SendData(INT8U u8Data){
	#if (8 ==  LCD_BiT_MODE)
	setBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 1 */
	LCD_DATA_PORT = u8Data;				/* upload  u8Data*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	
	
	#elif (4 ==  LCD_BiT_MODE)
	#ifdef LCD_UPPER_4_BITS
	setBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 1 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (u8Data & 0xF0);	/*Send the upper nibble first*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((u8Data & 0x0F) << 4);	/*Send the lower nibble second*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	#else
	setBit(LCD_CTRL_PORT, LCD_RS);	/* RS -> 1 */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((u8Data & 0xF0) >> 4);	/*Send the upper nibble first*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (u8Data & 0x0F);	/*Send the lower nibble second*/
	setBit(LCD_CTRL_PORT, LCD_EN);		/* high and low for EN */
	clearBit(LCD_CTRL_PORT, LCD_EN);
	_delay_us(40);						/* wait 40 us */
	#endif
	#endif
}
/*
Line 1: 0x00
Line 2: 0x40
*/
static void LCD_GotoXY(INT8U x, INT8U y){
	/* get address of DDRAM using x,y */
	if(x == 1){
		LCD_SendCmd((0x80|0x00) + y-1); /* Eqn */
	}
	else{
		LCD_SendCmd((0x80|0x40) + y-1); /* Eqn */
	}
}
void LCD_Init(void){
	/* Directions -> OUT */
	setBit(LCD_CTRL_DDR, LCD_RS);
	setBit(LCD_CTRL_DDR, LCD_EN);
	/*RW */
	setBit(LCD_CTRL_DDR, LCD_RW);
	clearBit(LCD_CTRL_PORT, LCD_RW);
	/*Back Light*/
	setBit(LCD_BL_DDR, LCD_BL_PIN);	
	setBit(LCD_BL_PORT, LCD_BL_PIN);		
	
	#if (8 ==  LCD_BiT_MODE)
	setAllBits(LCD_DATA_DDR);
	/* delay -> 20 ms (power on lcd) */
	_delay_ms(40);
	
	LCD_SendCmd(CMD_CFG_8_BIT);		/* 0x38 => 2 lines and 5x8 dots*/
	#elif (4 ==  LCD_BiT_MODE)
	#ifdef LCD_UPPER_4_BITS
	setBits(LCD_DATA_DDR, 0xF0);
	#else
	setBits(LCD_DATA_DDR, 0x0F);
	#endif
	/* delay -> 20 ms (power on lcd) */
	_delay_ms(40);
	LCD_SendCmd(CMD_INITIALIZE_CHIP);
	_delay_ms(5);
	LCD_SendCmd(CMD_INITIALIZE_CHIP);
	_delay_ms(5);
	LCD_SendCmd(CMD_INITIALIZE_CHIP);
	LCD_SendCmd(CMD_CFG_4_BIT_1);		/* 0x02 => Init LCD 4-bit mode This must be send first*/
	LCD_SendCmd(CMD_CFG_4_BIT_2);		/* 0x28 => 2 lines and 5x8 dots*/
	#endif
	LCD_SendCmd(CMD_DISP_ON);	/* 0x0C => Display on, no cursur, no bliking*/
	LCD_SendCmd(CMD_ENTRY_MODE);	/* 0x06 => cursur moves right, no display shift*/
	LCD_Clear();
}
void LCD_Clear(void){
	LCD_SendCmd(CMD_CLEAR);		/* 0x01 => Clear display*/
	_delay_ms(5);		/* delay 5 ms */
}
void LCD_DispChar(INT8U u8Char){
	LCD_SendData(u8Char);
}
void LCD_DispStr(INT8U* pu8Str){
	while (*pu8Str)
	{
		LCD_SendData(*pu8Str);
		pu8Str++;
	}
}
void LCD_DispCharXY(INT8U x, INT8U y, INT8U u8Char){
	LCD_GotoXY(x,y);
	LCD_DispChar(u8Char);
}
void LCD_DispStrXY(INT8U x, INT8U y, INT8U* pu8Str){
	LCD_GotoXY(x,y);
	LCD_DispStr(pu8Str);
}
void LCD_DispInt(int intNum){
	char a_bufferString[17]={0};
	sprintf(a_bufferString, "%3d", intNum);
	LCD_DispStr(a_bufferString);
}
void LCD_DispIntXY(INT8U x, INT8U y, int intNum){
	LCD_GotoXY(x,y);
	LCD_DispInt(intNum);
}
void LCD_displayRealNumber(double  Number ){	/*Example number = 123.0456*/
	char  a_str[17]={0};
	char *a_tmpSign = (Number < 0) ? "-" : "";
	float a_tmpVal = (Number < 0) ? -Number : Number;		/*remove the sign if negative*/
	int a_tmpInt1 = a_tmpVal;                  /* Get the integer part (123).*/
	float a_tmpFrac = a_tmpVal - a_tmpInt1;      /* Get fraction (0.0456).*/
	int a_tmpInt2 = a_tmpFrac * 10000;  		/* Turn into integer (456).*/
	/* Print as parts, note that you need 0-padding for fractional bit.*/
	sprintf (a_str, "%s%d.%4d", a_tmpSign, a_tmpInt1, a_tmpInt2);
	LCD_DispStr(a_str);
}
void LCD_displayRealNumberXY(INT8U x, INT8U y, double  Number ){
	LCD_GotoXY(x,y);
	LCD_displayRealNumber(Number);
}