/*
* RTC.c
*
* Created: 6/8/2020 3:23:43 PM
*  Author: Raafat
*/
#include "RTC.h"

/*Init each struct member.
* And hh, mm, etc... will be written over with the corresponding value
* This approach will not be using any third-party APIs like sprintf or itoa
*/
static RTC_Struct RTC = {{0},
						"hh:mm:ss",
						"dd/mm/20yy"};

void		RTC_Init(void){
	TWI_Init();	
}
RTC_Struct* RTC_Update(void){
	INT8U ind = 0;
	INT8U rtcRegisters[7] = {0};
	/*There should be checking for all TWI_xxxx functions except for TWI_Stop*/
	TWI_Start();
	TWI_WriteByte(RTC_SLA_W, SC_MT_SLA_ACK);
	TWI_WriteByte(0x00, SC_MT_DATA_ACK);
	TWI_Restart();
	TWI_WriteByte(RTC_SLA_R, SC_MT_SLA_ACK);
	for(ind = 0; ind < 6; ind++)
	{
		TWI_ReadByte(&rtcRegisters[ind], SC_MR_DATA_ACK);
	}
	TWI_ReadByte(&rtcRegisters[ind], SC_MR_DATA_NOTACK);
	TWI_Stop();
	
	/*Convert*/
	/*Sec*/
	RTC.RTC_RegValues[0] = rtcRegisters[0] & 0x0F;
	RTC.RTC_RegValues[0] += ((rtcRegisters[0] & 0x70)>>4)*10;
	RTC.RTC_Time[7]	= (rtcRegisters[0] & 0x0F) + '0';			/*"hh:mm:ss"*/
	RTC.RTC_Time[6] = (((rtcRegisters[0] & 0x70)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Min*/
	RTC.RTC_RegValues[1] = rtcRegisters[1] & 0x0F;
	RTC.RTC_RegValues[1] += ((rtcRegisters[1] & 0x70)>>4)*10;
	RTC.RTC_Time[4]	= (rtcRegisters[1] & 0x0F) + '0';			/*"hh:mm:ss"*/
	RTC.RTC_Time[3] = (((rtcRegisters[1] & 0x70)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Hr*/
	RTC.RTC_RegValues[2] = rtcRegisters[2] & 0x0F;
	RTC.RTC_RegValues[2] += ((rtcRegisters[2] & 0x30)>>4)*10;
	RTC.RTC_Time[1]	= (rtcRegisters[2] & 0x0F) + '0';			/*"hh:mm:ss"*/
	RTC.RTC_Time[0] = (((rtcRegisters[2] & 0x30)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Nth day in a week, starting by 1 = Sunday and So on i.e 1-7*/
	RTC.RTC_RegValues[3] = rtcRegisters[3] & 0x07;
	/*Day in a month from 1-31 */ 
	RTC.RTC_RegValues[4] = rtcRegisters[4] & 0x0F;
	RTC.RTC_RegValues[4] += ((rtcRegisters[4] & 0x30)>>4)*10;
	RTC.RTC_Date[1] = (rtcRegisters[4] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	RTC.RTC_Date[0] = ((rtcRegisters[4] & 0x30)>>4) + '0';			/*"dd/mm/20yy"*/
	/*month in a year from 1-12 */
	RTC.RTC_RegValues[5] = rtcRegisters[5] & 0x0F;
	RTC.RTC_RegValues[5] += ((rtcRegisters[5] & 0x10)>>4)*10;
	RTC.RTC_Date[4] = (rtcRegisters[5] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	RTC.RTC_Date[3] = ((rtcRegisters[5] & 0x10)>>4) + '0';			/*"dd/mm/20yy"*/
	/*least two digits in a 20xx years  00-99, ex: the year 2023 is just 23*/
	RTC.RTC_RegValues[6] = rtcRegisters[6] & 0x0F;
	RTC.RTC_RegValues[6] += ((rtcRegisters[6] & 0xF0)>>4)*10;
	RTC.RTC_Date[9] = (rtcRegisters[6] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	RTC.RTC_Date[8] = ((rtcRegisters[6] & 0xF0)>>4) + '0';			/*"dd/mm/20yy"*/
	
	return &RTC;
}