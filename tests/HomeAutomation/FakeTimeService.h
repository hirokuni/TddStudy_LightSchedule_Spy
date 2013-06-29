#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

/**********************************************************
 *
 * FakeTimeService is responsible for ...
 *
 **********************************************************/

#include "TimeService.h"

enum{
	TIME_UNKNOWN = -1
};

void FakeTimeService_Create(void);
void FakeTimeService_Destroy(void);
void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(Day day);


#endif  /* D_FakeFakeTimeService_H */
