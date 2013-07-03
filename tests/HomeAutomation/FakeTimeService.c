#include "FakeTimeService.h"
#include "stdio.h"
static int minuteOfDay = TIME_UNKNOWN;
static int dayOfWeek = TIME_UNKNOWN;
static int callBackIntervalTime;
static void (*savedCallbackFunction)(void);

void FakeTimeService_Create(void)
{
	minuteOfDay = TIME_UNKNOWN;
	dayOfWeek = TIME_UNKNOWN;
	callBackIntervalTime = -1;
	savedCallbackFunction = NULL;
}

void FakeTimeService_Destroy(void)
{
}

void FakeTimeService_SetDay(Day day){
dayOfWeek = day;
}

void FakeTimeService_SetMinute(int minute){
	minuteOfDay = minute;
}

int getMinuteOfDay(void){
	return minuteOfDay;
}

int getDayOfWeek(void){
	return dayOfWeek;
}

void TimeService_SetPeriodicAlarmInSeconds(int sec, WakeupCallback cb){
	 callBackIntervalTime = sec;
	 savedCallbackFunction = cb;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb){
	if(cb == savedCallbackFunction && callBackIntervalTime == seconds)
	{
		savedCallbackFunction = NULL;
		callBackIntervalTime = 0;
	}
}



void * FakeTimeService_GetAlarmCallback(void){
	return (void*)savedCallbackFunction;
}

int FakeTimeService_GetAlarmPeriod(void){
	return callBackIntervalTime;
}
