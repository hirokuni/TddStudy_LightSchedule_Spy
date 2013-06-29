#ifndef D_LightSchedule_H
#define D_LightSchedule_H

/**********************************************************
 *
 * LightSchedule is responsible for ...
 *
 **********************************************************/

#include "TimeService.h"

void LightSchedule_Create(void);
void LightSchedule_Destroy(void);
void LightScheduler_Wakeup(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);

#endif  /* D_FakeLightSchedule_H */
