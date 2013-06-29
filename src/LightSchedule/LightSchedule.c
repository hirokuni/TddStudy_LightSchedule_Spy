#include "LightSchedule.h"
#include "LightController.h"

typedef struct {
	int id;
	Day day;
	int minuteOfDay;
	int event;
} ScheduleEvent;

ScheduleEvent scheduleEvent;

static int UNUSED = -1;
enum {
	LIGHT_COMMAND_INITIAL_VAL = -1, LIGHT_COMMAND_ON = 0, LIGHT_COMMAND_OFF
};
void LightSchedule_Create(void) {
	scheduleEvent.id = UNUSED;
	scheduleEvent.event = LIGHT_COMMAND_INITIAL_VAL;
}

void LightSchedule_Destroy(void) {
}

void LightScheduler_Wakeup(void) {
	int minuteOfDay = -1;

	minuteOfDay = getMinuteOfDay();

	if (scheduleEvent.id == UNUSED)
		return;

	if (minuteOfDay != scheduleEvent.minuteOfDay)
		return;

	if (scheduleEvent.event == LIGHT_COMMAND_ON) {
		LightController_On(scheduleEvent.id);
	} else if (scheduleEvent.event == LIGHT_COMMAND_OFF) {
		LightController_Off(scheduleEvent.id);
	} else {
		return;
	}

}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
	scheduleEvent.id = id;
	scheduleEvent.day = day;
	scheduleEvent.minuteOfDay = minuteOfDay;
	scheduleEvent.event = LIGHT_COMMAND_ON;
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
	scheduleEvent.id = id;
	scheduleEvent.day = day;
	scheduleEvent.minuteOfDay = minuteOfDay;
	scheduleEvent.event = LIGHT_COMMAND_OFF;
}
