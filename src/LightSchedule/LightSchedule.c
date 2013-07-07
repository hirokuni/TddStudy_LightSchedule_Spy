#include "LightSchedule.h"
#include "LightController.h"
#define TRUE 1
#define FALSE 0

typedef struct {
	int id;
	Day day;
	int minuteOfDay;
	int event;
} ScheduleEvent;

#define MAX_EVENTS 128

ScheduleEvent scheduleEvent;
ScheduleEvent scheduleEvents[MAX_EVENTS];

static int UNUSED = -1;
enum {
	LIGHT_COMMAND_INITIAL_VAL = -1, TURN_ON = 0, TURN_OFF
};
void LightSchedule_Create(void) {
	int i = 0;
	scheduleEvent.id = UNUSED;
	scheduleEvent.event = LIGHT_COMMAND_INITIAL_VAL;

	for (i = 0; i < MAX_EVENTS; i++) {
		scheduleEvents[i].id = UNUSED;
	}

	TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightSchedule_Destroy(void) {
	TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

static int DoesLightRespondToday(int reactionDay) {
	int today = getDayOfWeek();

	if (reactionDay == EVERYDAY)
		return TRUE;

	if (reactionDay == today)
		return TRUE;

	if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
		return TRUE;

	if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
		return TRUE;

	return FALSE;
}

/*
 * この関数は条件に従って単独イベントをトリガーする債務がある。複数イベントをサポートするときには、
 * この関数はループから呼び出せばよい。（呼び出すループ内にこの関数のロジックをいれると
 * ループが長くなって見づらい関数になってしまう）
 */
static void processEventDueNow(ScheduleEvent* lightEvent) {
	int minuteOfDay = -1;
	minuteOfDay = getMinuteOfDay();

	if (lightEvent->id == UNUSED)
		return;

	if (!DoesLightRespondToday(lightEvent->day))
		return;

	if (minuteOfDay != lightEvent->minuteOfDay)
		return;

	if (lightEvent->event == TURN_ON) {
		LightController_On(lightEvent->id);
	} else if (lightEvent->event == TURN_OFF) {
		LightController_Off(lightEvent->id);
	} else {
		return;
	}
}

/*
 * LightScheduler_Wakeupは周期的なコールバック関数としてTimeServiceに登録される関数になる。
 * 今のところは単独エベントしか処理しないが、あおtでスケジュールイベントのコレクションに含まれる各
 * イベントを処理するようになる。
 */
void LightScheduler_Wakeup(void) {
	int i;
	for (i = 0; i < MAX_EVENTS; i++)
		processEventDueNow(&scheduleEvents[i]);

	processEventDueNow(&scheduleEvent);
}

/*
 * setScheduleEventを公開しない理由は、パラメータのリストが既に長かったため。
 * 公開するとクライアントのコードの負担が増えるから。ここの関数を列挙する方が
 * コードの意図がわかりやすく安全である。
 */
static LightScheduleResult setScheduleEvent(int id, Day day, int minuteOfDay,
		int event) {
	int i;

	if (id < 0 || id > 31)
		return LS_ID_OUT_OF_BOUNDS;

	for (i = 0; i < MAX_EVENTS; i++) {
		if (scheduleEvents[i].id == UNUSED) {
			scheduleEvents[i].id = id;
			scheduleEvents[i].day = day;
			scheduleEvents[i].minuteOfDay = minuteOfDay;
			scheduleEvents[i].event = event;
			return LS_OK;
		}
	}

	return LS_TOO_MANY_EVENTS;
}

LightScheduleResult LightScheduler_ScheduleTurnOn(int id, Day day,
		int minuteOfDay) {
	return setScheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
	setScheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay){
	int i;
		for (i = 0; i < MAX_EVENTS; i++) {
			if (scheduleEvents[i].id != UNUSED) {
				if(scheduleEvents[i].id == id && scheduleEvents[i].day == day && scheduleEvents[i].minuteOfDay == minuteOfDay)
				scheduleEvents[i].id = UNUSED;
				return;
			}
		}
}
