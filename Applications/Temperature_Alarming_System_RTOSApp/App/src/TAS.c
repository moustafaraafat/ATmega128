/*
* TAS.c
*
* Created: 6/9/2020 11:58:59 AM
*  Author: Raafat
*/
#if 1

#include "TAS.h"

TAS_Struct TAS = {SS_MAIN, YES, 0};	/*Initials*/


void TAS_Init(void){
	LCD_Init();
	ADC_Init();
	Key_Init();
	Buz_Init();
	Led_Init();		/*PB4 LED*/
	Leds_Init(0xFF);		/*PA LEDs*/
	Uart_Init(UART_0, 9600);
	
	/*Get T and noOfAlarms Values from EEPROM*/
	TAS.threshTemp = EEPROM_read(T_LOCATION_EEPROM);
	if(TAS.threshTemp == 0xFF){  /*if first run after a burn*/
		TAS.threshTemp = 100;
	}
	TAS.noOfAlarms = EEPROM_read(NA_LOCATION_EEPROM);
	if(TAS.noOfAlarms == 0xFF){   /*if first run after a burn*/
		TAS.noOfAlarms = 0;
	}
	/*Init with main state display*/
	TAS_DispState();
	TAS_DispT();
	TAS_DispAA();
	TAS_DispC();
}
void TAS_DispAA(void){
	LCD_DispCharXY(DISP_LINE, DISP_IND_AA, TAS.alarmAct);
}
void TAS_DispC(void){
	LCD_DispIntXY(DISP_LINE, DISP_IND_C, TAS.currentTemp);
}
void TAS_DispT(void){
	LCD_DispIntXY(DISP_LINE, DISP_IND_T, TAS.threshTemp);
}

void TAS_DispNoOfAlarms(void){
	LCD_DispIntXY(DISP_LINE, DISP_IND_NO_ALARMS, TAS.noOfAlarms);
}
void TAS_DispState(void){
	switch(TAS.systemState)
	{
		case SS_MAIN:
		LCD_DispStrXY(1, 1, DISP_MAIN_L1);
		LCD_DispStrXY(2, 1, DISP_MAIN_L2);
		break;
		case SS_KEY_CFG:
		LCD_DispStrXY(1, 1, DISP_KEY_CFG_L1);
		LCD_DispStrXY(2, 1, DISP_KEY_CFG_L2);
		break;
		case SS_TERM_CFG:
		LCD_DispStrXY(1, 1, DISP_TERM_CFG_L1);
		LCD_DispStrXY(2, 1, DISP_TERM_CFG_L2);
		break;
		case SS_ALARM:
		LCD_DispStrXY(1, 1, DISP_ALARM_L1);
		LCD_DispStrXY(2, 1, DISP_ALARM_L2);
		break;
		case SS_HISTORY:
		LCD_DispStrXY(1, 1, DISP_HISTORY_L1);
		LCD_DispStrXY(2, 1, DISP_HISTORY_L2);
		break;
		case SS_NONE:
		break;
	}
}
Bool TAS_UpdateC(void){
	Bool result = FALSE;
	INT16U temp = ADC_Read(0);
	temp = (temp*150UL)/1023;	/*0:1023 to 0:150 C*/
	if(temp != TAS.currentTemp){
		TAS.currentTemp = temp;
		result = TRUE;
	}
	
	return result;
}
void TAS_ToggleAA(void){
	if(TAS.alarmAct == YES){
		TAS.alarmAct = NO;
		}else{
		TAS.alarmAct = YES;
	}
}
void TAS_UpdateT(void){
	EEPROM_write(T_LOCATION_EEPROM, TAS.threshTemp);
}
void TAS_UpdateNoOfAlarms(void){
	TAS.noOfAlarms++;
	EEPROM_write(NA_LOCATION_EEPROM, TAS.noOfAlarms);
}


#endif