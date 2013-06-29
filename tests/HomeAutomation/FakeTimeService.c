#include "FakeTimeService.h"

static int minuteOfDay = TIME_UNKNOWN;
static int dayOfWeek = TIME_UNKNOWN;

void FakeTimeService_Create(void)
{
	minuteOfDay = TIME_UNKNOWN;
	dayOfWeek = TIME_UNKNOWN;
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
