#ifndef D_LightSchedule_H
#define D_LightSchedule_H

/**********************************************************
 *
 * LightSchedule is responsible for ...
 *
 **********************************************************/

#include "TimeService.h"
typedef enum {
	LS_OK,LS_TOO_MANY_EVENTS,LS_ID_OUT_OF_BOUNDS
}LightScheduleResult;

void LightSchedule_Create(void);
void LightSchedule_Destroy(void);
void LightScheduler_Wakeup(void);
LightScheduleResult LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);
#endif  /* D_FakeLightSchedule_H */
