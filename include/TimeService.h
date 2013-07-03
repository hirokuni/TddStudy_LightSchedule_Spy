/*
 * TimeService.h
 *
 *  Created on: 2013/06/24
 *      Author: hirokuni
 */

#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

enum Day { EVERYDAY = -1, WEEKEND = -2, WEEKDAY = -3,
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

typedef enum Day Day;

typedef void (*WakeupCallback)(void);

int getMinuteOfDay(void);
int getDayOfWeek(void);
void TimeService_SetPeriodicAlarmInSeconds(int sec,  WakeupCallback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback);


#endif /* TIMESERVICE_H_ */
