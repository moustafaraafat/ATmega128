/*
* mainApp.c
*
* Created: 7/10/2020 9:04:51 PM
*  Author: Raafat
*/
#if 1

/*include FreeRTOS files*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/*include app files*/
#include "TAS.h"
/*Global variables*/
extern TAS_Struct TAS;
INT8U		key = 0;INT8U		digitInd = 0;INT8U		ind = 0;INT8U		digits[3] = {0};INT8U		data = 0;INT8U		threshTemp = 0;
/* Prototype for Tasks */
void T_Check		(void* pvData);
void T_CUpdate		(void* pvData);
void T_Alarm		(void* pvData);
void T_KeyHandler	(void* pvData);
void T_TermHandler	(void* pvData);
void T_Disp			(void* pvData);
/* OS Services Declaration */EventGroupHandle_t		egAlarm;EventBits_t				ebAlarm;
EventGroupHandle_t		egDisp;EventBits_t				ebDisp;
xSemaphoreHandle		bsTCheck;


int main(void){
	/* Init Peripherals */	TAS_Init();	/* OS Services Create and Init.*/	egAlarm = xEventGroupCreate();	egDisp = xEventGroupCreate();	vSemaphoreCreateBinary(bsTCheck, 0);	/* Tasks Create */	xTaskCreate(T_Check,		"T_Check",			150, NULL, 5, NULL);	xTaskCreate(T_CUpdate,		"T_CUpdate",		150, NULL, 2, NULL);	xTaskCreate(T_Alarm,		"T_Alarm",			150, NULL, 6, NULL);	xTaskCreate(T_KeyHandler,	"T_KeyHandler",		150, NULL, 4, NULL);	xTaskCreate(T_TermHandler,	"T_TermHandler",	150, NULL, 3, NULL);	xTaskCreate(T_Disp,			"T_Disp",			150, NULL, 1, NULL);	/* Start OS or Scheduler */	vTaskStartScheduler();
}

/*This task responsible for checking whether C > T, 
Will work ONLY if either of them changes, such that a bsTCheck semaphore is given*/
void T_Check		(void* pvData){
	while (1)
	{
		if(xSemaphoreTake(bsTCheck, portMAX_DELAY))
		{
			switch(TAS.systemState)
			{
				case SS_MAIN:
				if((TAS.currentTemp >= TAS.threshTemp) && (TAS.alarmAct == YES))
				{
					TAS.systemState = SS_ALARM;
					TAS_UpdateNoOfAlarms();
					xEventGroupSetBits(egAlarm, E_ALARM);
					xEventGroupSetBits(egDisp, E_DISP_SS_ALARM);
				}
				else
				{
					xEventGroupClearBits(egAlarm, E_ALARM);
				}
				break;
				case SS_ALARM:
				if(TAS.currentTemp < TAS.threshTemp)
				{
					TAS.systemState = SS_MAIN;
					xEventGroupClearBits(egAlarm, E_ALARM);
					xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
				}
				break;
				default:
				break;
			}
		}
	}
}
/*This Task responsible for updating C, works periodically (100 Ticks)*/
void T_CUpdate		(void* pvData){
	while(1)
	{
		switch(TAS.systemState)
		{
			case SS_MAIN:
			if(TAS_UpdateC())
			{
				xEventGroupSetBits(egDisp, E_DISP_C);
				xSemaphoreGive(bsTCheck);
			}
			break;
			case SS_ALARM:
			if(TAS_UpdateC()){
				xSemaphoreGive(bsTCheck);
			}
			break;
			default:
			break;
		}
		vTaskDelay(100);
	}
}
/*This Task responsible for Alarming effect*/
void T_Alarm		(void* pvData){
	while(1){		ebAlarm = xEventGroupWaitBits(egAlarm,		E_ALARM,		pdFALSE,	/*Wait, but don't clear (cyclic)*/		pdTRUE,  /*It's the same*/		portMAX_DELAY);				if( ebAlarm & E_ALARM )		{			Led_On();			Leds_On(0xFF);			Buz_On();			vTaskDelay(500);	/*Go wait, to be able to recheck the temp*/			Led_Off();			Leds_Off(0xFF);			Buz_Off();			vTaskDelay(500);	/*Go wait, to be able to recheck the temp*/		}	}
}
/*This Task responsible for taking any input through the keypad*/
void T_KeyHandler	(void* pvData){
	while(1)
	{
		key = Key_GetKey();
		switch(TAS.systemState)
		{
			case SS_MAIN:
			if(key == 15){
				TAS.systemState = SS_KEY_CFG;
				xEventGroupSetBits(egDisp, E_DISP_SS_KEY_CFG);
			}
			else if(key == 13){
				TAS_ToggleAA();
				xEventGroupSetBits(egDisp, E_DISP_AA);
				xSemaphoreGive(bsTCheck);
			}
			else if(key == 14){
				TAS.systemState = SS_HISTORY;
				xEventGroupSetBits(egDisp, E_DISP_SS_HISTORY);
			}
			break;
			case SS_KEY_CFG:
			if(key == 12){
				TAS.systemState = SS_MAIN;
				digitInd = 0;
				xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
			}
			else if(key == 15){
				TAS.systemState = SS_MAIN;
				threshTemp = 0;
				for(ind = 0; ind < digitInd; ind++){
					threshTemp = threshTemp*10 + digits[ind];
				}
				digitInd = 0;
				TAS.threshTemp = threshTemp;
				TAS_UpdateT();		/*Update T in the EEPROM*/
				xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
				xSemaphoreGive(bsTCheck);
			}
			else if((key >= 1) && (key <= 10) && (digitInd < 3)){
				if(key == 10){
					key = 0;
				}
				xEventGroupSetBits(egDisp, E_DISP_T);
				digits[digitInd] = key;
				digitInd++;
			}
			break;
			case SS_ALARM:
			if(key == 12){
				TAS.systemState = SS_MAIN;
				TAS.alarmAct = NO;
				xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
				xSemaphoreGive(bsTCheck);
			}
			break;
			case SS_HISTORY:
			if(key == 15){
				TAS.systemState = SS_MAIN;
				xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
			}
			break;
			default:
			break;
		}
		vTaskDelay(50);
	}
}
/*This Task responsible for taking any input through the terminal*/
void T_TermHandler	(void* pvData){
	while(1)
	{
		switch(TAS.systemState)
		{
			case SS_MAIN:
			if(Uart_ReceiveByte_Unblock(UART_0, &data))
			{
				if(data == 'G'){
					TAS.systemState = SS_TERM_CFG;
					xEventGroupSetBits(egDisp, E_DISP_SS_TERM_CFG);
				}
			}
			break;
			case SS_TERM_CFG:
			if(Uart_ReceiveByte_Unblock(UART_0, &data))
			{
				if(data == 'C'){
					TAS.systemState = SS_MAIN;
					digitInd = 0;
					xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
				}
				else if(data == 'O'){
					TAS.systemState = SS_MAIN;
					threshTemp = 0;
					for(ind = 0; ind < digitInd; ind++){
						threshTemp = threshTemp*10 + digits[ind];
					}
					digitInd = 0;
					TAS.threshTemp = threshTemp;
					TAS_UpdateT();		/*Update T in the EEPROM*/
					xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
					xSemaphoreGive(bsTCheck);
				}
				else if((data >= '0') && (data <= '9') && (digitInd < 3)){
					xEventGroupSetBits(egDisp, E_DISP_T);
					digits[digitInd] = data - '0';
					digitInd++;
				}
			}
			break;
			case SS_ALARM:
			if(Uart_ReceiveByte_Unblock(UART_0, &data))
			{
				if(data == 'S')
				{
					TAS.systemState = SS_MAIN;
					TAS.alarmAct = NO;
					xEventGroupSetBits(egDisp, E_DISP_SS_MAIN);
					xSemaphoreGive(bsTCheck);
				}
			}
			break;
			default:
			break;
		}
		vTaskDelay(50);
	}
}
/*This Task responsible for displaying different screens for each state and C, T and AA*/
void T_Disp			(void* pvData){
	while(1)
	{
		ebDisp = xEventGroupWaitBits(egDisp,		E_DISP_SS_MAIN | E_DISP_SS_KEY_CFG | E_DISP_SS_TERM_CFG | E_DISP_SS_ALARM		| E_DISP_SS_HISTORY | E_DISP_C | E_DISP_T | E_DISP_AA,		pdTRUE,	/*Wait, and Clear*/		pdFALSE,  /*We wait for individual events*/		portMAX_DELAY);
		
		if (ebDisp & E_DISP_SS_MAIN)
		{
			TAS_DispState();
			TAS_DispT();
			TAS_DispAA();
			TAS_DispC();
		}
		else if (ebDisp & E_DISP_SS_KEY_CFG)
		{
			TAS_DispState();
		}
		else if (ebDisp & E_DISP_SS_TERM_CFG)
		{
			TAS_DispState();
		}
		else if (ebDisp & E_DISP_SS_ALARM)
		{
			TAS_DispState();
		}
		else if (ebDisp & E_DISP_SS_HISTORY)
		{
			TAS_DispState();
			TAS_DispNoOfAlarms();
		}
		else if (ebDisp & E_DISP_C)
		{
			TAS_DispC();
		}
		else if (ebDisp & E_DISP_T)
		{
			if(TAS.systemState == SS_TERM_CFG){
				LCD_DispCharXY(DISP_LINE, DISP_IND_T + digitInd, data);
			}
			else if(TAS.systemState == SS_KEY_CFG){
				LCD_DispCharXY(DISP_LINE, DISP_IND_T + digitInd, key + '0');
			}
			else{
				TAS_DispT();
			}
		}
		else if (ebDisp & E_DISP_AA)
		{
			TAS_DispAA();
		}
	}
}


#endif