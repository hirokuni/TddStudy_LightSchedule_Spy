/*
 * TimeService.h
 *
 *  Created on: 2013/06/24
 *      Author: hirokuni
 */

#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

enum { EVERYDAY = -1, WEEKEND = -2, WEEKDAY = -3,
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

int getMinuteOfDay(void);
int getDayOfWeek(void);

#endif /* TIMESERVICE_H_ */
