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
	LIGHT_COMMAND_INITIAL_VAL = -1, TURN_ON = 0, TURN_OFF
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

	if (scheduleEvent.event == TURN_ON) {
		LightController_On(scheduleEvent.id);
	} else if (scheduleEvent.event == TURN_OFF) {
		LightController_Off(scheduleEvent.id);
	} else {
		return;
	}
}

/*
 * setScheduleEventを公開しない理由は、パラメータのリストが既に長かったため。
 * 公開するとクライアントのコードの負担が増えるから。ここの関数を列挙する方が
 * コードの意図がわかりやすく安全である。
 */
static void setScheduleEvent(int id, Day day, int minuteOfDay, int event) {
	scheduleEvent.id = id;
	scheduleEvent.day = day;
	scheduleEvent.minuteOfDay = minuteOfDay;
	scheduleEvent.event = event;
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay) {
	setScheduleEvent(id,day,minuteOfDay,TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
	setScheduleEvent(id,day,minuteOfDay,TURN_OFF);
}
