/*
 * TAS.h
 *
 * Created: 6/9/2020 11:58:47 AM
 *  Author: Raafat
 *	Module: Temperature Alarming System (TAS)
 */ 

#if 1

#ifndef TAS_H_
#define TAS_H_


#include	"board.h"
#include	"keypad.h"
#include	"lcd.h"
#include	"adc.h"
#include	"uart.h"
#include	"eeprom.h"

typedef enum{
	SS_NONE, SS_MAIN, SS_KEY_CFG, SS_TERM_CFG, SS_ALARM, SS_HISTORY
}System_State;

typedef enum{
	YES = 'Y', NO = 'N'
}Alarm_Act;

typedef struct{
	System_State	systemState;	/*SS*/
	Alarm_Act		alarmAct;		/*AA*/
	INT8U			currentTemp;	/*C*/
	INT8U			threshTemp;		/*T*/
	INT8U			noOfAlarms;		/*NA*/
}TAS_Struct;

#define		DISP_MAIN_L1			"C:    T:    AA: "
#define		DISP_MAIN_L2			"K15 TG AC13 AH14"

#define		DISP_ALARM_L1			"    ALARMING    "
#define		DISP_ALARM_L2			"  KAD:12 TAD:S  "

#define		DISP_KEY_CFG_L1			"      T:        "
#define		DISP_KEY_CFG_L2			"  OK:15  CN:12  "

#define		DISP_TERM_CFG_L1		"      T:        "
#define		DISP_TERM_CFG_L2		"   OK:O  CN:C   "

#define		DISP_HISTORY_L1			"No Of Alarms:   "
#define		DISP_HISTORY_L2			"  Cancel: 15    "

#define		DISP_LINE				1
#define		DISP_LINE2				2
#define		DISP_IND_C				3
#define		DISP_IND_T				9
#define		DISP_IND_AA				16
#define		DISP_IND_NO_ALARMS		14

#define		T_LOCATION_EEPROM		0
#define		NA_LOCATION_EEPROM		1

/*Event Group bits*/
/*For egAlarm*/
#define E_ALARM				(1<<0)
/*For egDisp*/
#define E_DISP_SS_MAIN		(1<<0)
#define E_DISP_SS_KEY_CFG	(1<<1)
#define E_DISP_SS_TERM_CFG	(1<<2)
#define E_DISP_SS_ALARM		(1<<3)
#define E_DISP_SS_HISTORY	(1<<4)
#define E_DISP_C			(1<<5)
#define E_DISP_T			(1<<6)
#define E_DISP_AA			(1<<7)


/*Init*/
void TAS_Init(void);
/*Displaying*/
void TAS_DispAA(void);
void TAS_DispC(void);
void TAS_DispT(void);
void TAS_DispState(void);
void TAS_DispNoOfAlarms(void);
/*TAS Structure Manipulation*/
Bool TAS_UpdateC(void);
void TAS_ToggleAA(void);
void TAS_UpdateT(void);				/*Update and write to EEPROM*/
void TAS_UpdateNoOfAlarms(void);	/*Update and write to EEPROM*/
//void TAS_UpdateRTC(void);			/*Update and write to EEPROM*/


#endif /* TAS_H_ */

#endif