/*
 * keypad.c
 *
 * Created: 5/21/2020 1:01:43 PM
 *  Author: Raafat
 */ 
#include "keypad.h"

/*  //For returning the real value on Keypad not from 1 to 16
INT8U keys[4][4] = {
	{'7',		'8',		'9',		'/'},
	{'4',		'5',			'6',		'*'},
	{'1',		'2',		'3',		'-'},
	{'C',		'0',		'=',	'+'}
};
*/
void Key_Init(void){
	/*Init Rows as output and init with 1's*/
	setBits(KEY_DDR, KEY_ROWS_MSK);
	setBits(KEY_PORT, KEY_ROWS_MSK);
	/*Init Cols as Input and pulled up*/
	clearBits(KEY_DDR, KEY_COLS_MSK);
	setBits(KEY_PORT, KEY_COLS_MSK);
}
INT8U Key_GetKey(void){
	INT8U rows = 0, cols = 0,  key = 0;
	for(rows = 0; rows < 4; rows++){
		clearBit(KEY_PORT, rows);
		/*Delay may be required here*/
		_delay_ms(1);	
		for(cols = 0; cols < 4; cols++){
			if(!readBit(KEY_PINR, cols+4)) {
				while(!readBit(KEY_PINR, cols+4));
				key = cols + 4*rows + 1;
			//key = keys[rows][cols];
				return key;
				}
		}
		setBit(KEY_PORT, rows);
	}
	return KEY_NONE;
}