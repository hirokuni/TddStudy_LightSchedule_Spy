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
 * ���̊֐��͏����ɏ]���ĒP�ƃC�x���g���g���K�[�����������B�����C�x���g���T�|�[�g����Ƃ��ɂ́A
 * ���̊֐��̓��[�v����Ăяo���΂悢�B�i�Ăяo�����[�v���ɂ��̊֐��̃��W�b�N��������
 * ���[�v�������Ȃ��Č��Â炢�֐��ɂȂ��Ă��܂��j
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
 * LightScheduler_Wakeup�͎����I�ȃR�[���o�b�N�֐��Ƃ���TimeService�ɓo�^�����֐��ɂȂ�B
 * ���̂Ƃ���͒P�ƃG�x���g�����������Ȃ����A����t�ŃX�P�W���[���C�x���g�̃R���N�V�����Ɋ܂܂��e
 * �C�x���g����������悤�ɂȂ�B
 */
void LightScheduler_Wakeup(void) {
	int i;
	for (i = 0; i < MAX_EVENTS; i++)
		processEventDueNow(&scheduleEvents[i]);

	processEventDueNow(&scheduleEvent);
}

/*
 * setScheduleEvent�����J���Ȃ����R�́A�p�����[�^�̃��X�g�����ɒ����������߁B
 * ���J����ƃN���C�A���g�̃R�[�h�̕��S�������邩��B�����̊֐���񋓂������
 * �R�[�h�̈Ӑ}���킩��₷�����S�ł���B
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
