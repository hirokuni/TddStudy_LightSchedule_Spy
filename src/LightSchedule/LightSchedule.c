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
 * ���̊֐��͏����ɏ]���ĒP�ƃC�x���g���g���K�[�����������B�����C�x���g���T�|�[�g����Ƃ��ɂ́A
 * ���̊֐��̓��[�v����Ăяo���΂悢�B�i�Ăяo�����[�v���ɂ��̊֐��̃��W�b�N��������
 * ���[�v�������Ȃ��Č��Â炢�֐��ɂȂ��Ă��܂��j
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
 * LightScheduler_Wakeup�͎����I�ȃR�[���o�b�N�֐��Ƃ���TimeService�ɓo�^�����֐��ɂȂ�B
 * ���̂Ƃ���͒P�ƃG�x���g�����������Ȃ����A����t�ŃX�P�W���[���C�x���g�̃R���N�V�����Ɋ܂܂��e
 * �C�x���g����������悤�ɂȂ�B
 */
void LightScheduler_Wakeup(void) {
	processEventDueNow(&scheduleEvent);
}

/*
 * setScheduleEvent�����J���Ȃ����R�́A�p�����[�^�̃��X�g�����ɒ����������߁B
 * ���J����ƃN���C�A���g�̃R�[�h�̕��S�������邩��B�����̊֐���񋓂������
 * �R�[�h�̈Ӑ}���킩��₷�����S�ł���B
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
