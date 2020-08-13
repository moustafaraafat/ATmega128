/*
 * RTC.h
 *
 * Created: 6/8/2020 3:23:34 PM
 *  Author: Raafat
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "TWI.h"

#define RTC_SLA_W	0b11010000
#define RTC_SLA_R	0b11010001

typedef struct{
	INT8U RTC_RegValues[7];	/*ss, mm, hh, day (nth day in a week), dd, mm, yy*/
	INT8U RTC_Time[9];		/*"hh:mm:ss"*/
	INT8U RTC_Date[11];		/*"dd/mm/20yy"*/
}RTC_Struct;

void		RTC_Init(void);
RTC_Struct* RTC_Update(void);


#endif /* RTC_H_ */