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

ScheduleEvent scheduleEvent;

static int UNUSED = -1;
enum {
	LIGHT_COMMAND_INITIAL_VAL = -1, TURN_ON = 0, TURN_OFF
};
void LightSchedule_Create(void) {
	scheduleEvent.id = UNUSED;
	scheduleEvent.event = LIGHT_COMMAND_INITIAL_VAL;
	TimeService_SetPeriodicAlarmInSeconds(60,LightScheduler_Wakeup);
}

void LightSchedule_Destroy(void) {
	TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

static int DoesLightRespondToday(int reactionDay) {
	int today = getDayOfWeek();

	if (reactionDay == EVERYDAY)
		return TRUE;

	if(reactionDay == today)
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

	if (scheduleEvent.id == UNUSED)
		return;

	if(!DoesLightRespondToday(scheduleEvent.day))
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
 * LightScheduler_Wakeupは周期的なコールバック関数としてTimeServiceに登録される関数になる。
 * 今のところは単独エベントしか処理しないが、あおtでスケジュールイベントのコレクションに含まれる各
 * イベントを処理するようになる。
 */
void LightScheduler_Wakeup(void) {
	processEventDueNow(&scheduleEvent);
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
	setScheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay) {
	setScheduleEvent(id, day, minuteOfDay, TURN_OFF);
}
