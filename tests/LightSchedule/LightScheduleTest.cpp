extern "C" {
#include "LightSchedule.h"
#include "LightControllerSpy.h"
#include "TimeService.h"
#include "HomeAutomation/FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightSchedule) {
	void setup() {
		LightSchedule_Create();
		LightController_Create();
	}

	void teardown() {
		LightSchedule_Destroy();
		LightController_Destroy();
	}
	void setTimeTo(Day day, int minuteOfDay) {
		FakeTimeService_SetDay(day);
		FakeTimeService_SetMinute(minuteOfDay);
	}

	void checkLightState(int id, int level) {
		if (id == LIGHT_ID_UNKNOWN) {
			LONGS_EQUAL(id, LightControllerSpy_GetLastID());
			LONGS_EQUAL(level, LightControllerSpy_GetLastState());
		} else {
			LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
		}
	}
};

/*
 * �ŏ��̃e�X�g�ɂ��Ă͉��L�̃R�[�h�͑傫������B���̃e�X�g�����{����ɂ́A��̃e�X�g�_�u��(FakeTimeService�ALightController spy)��
 * �v���_�N�g�R�[�h�̃X�P���g���������e�K�v������B�������A����炷�ׂẴs�[�X�����܂��g�ݍ��킹�Ȃ���ΐ���Ȃ��B�Ƃ肠�������̃e�X�g��
 * �R�����g�A�E�g����B
 */
//TEST(LightSchedule, ScheduleOnEverydatyNotTimeYet) {
//	/*
//	 * LightScheduler���e�X�g���邽�߂ɕK�v��LightControllerSpy��FakeTimeService��
//	 * �������l����̂ɖ𗧂e�X�g�P�[�X��������(�}8-4�@���C�g�X�P�W���[���@�\�̃��j�b�g�e�X�g�\�����Q�Ɓj
//	 */
//	//����(Everyday)�A1200����(�ߌ�8���j��ID���R�̃��C�g���I���ɂ���悤�X�P�W���[������B
//	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
//	//���Ɏ��v���R���g���[�����āA���j���̌ߌ�7��59��(1199����)�ɃZ�b�g����FakeTimeService�Ɏw�����Ă���B
//	FakeTimeService_SetDay (MONDAY);
//	FakeTimeService_SetMinute(1199);
//
//	/*
//	 * Execute
//	 */
//	//�v���_�N�g�R�[�h��TimeService(�}8-4�Q�Ɓj����������Ă���悤�ɁA
//	//LightScheduler_Wakeup()�̃R�[���o�b�N���V�~�����[�g����B
//	LightScheduler_Wakeup();
//
//	/*
//	 * Verify
//	 */
//	//MONDAY, 1199���ڂ̓X�P�W���[�����ꂽ�����ł͂Ȃ����߁ALightController�̊֐��͌Ăяo����Ȃ��͂�(xxx_UNKNOWN���ԋp�����͂��j�B
//	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
//	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
//
//}
/*
 *  �ŏ��̃e�X�g�Ƃ��Ă҂�����Ȃ̂́A���̂悤�ɏ��������ɉ����N����ׂ����𖾊m�ɂ���e�X�g���낤�B
 * ���̃e�X�g�͊ȒP�ɑg�ݗ��Ă��邵�A�t�B�[�h�o�b�N�������ɓ�����BLightScheduler�ɂ�
 * �����K�v�Ȃ��̂ŁA�e�X�g�_�u���̏����ɏW���ł���B
 *  ����OS���܂��I�肵�Ă��Ȃ�������A���C�g���R���g���[������́[�ǂ��������܂��v��i�K�ł���΁A�ǂ�����H
 * ����炪���܂�܂Ŏ������~�߂Ȃ��Ă͂Ȃ�Ȃ��̂��H
 * 	������񂻂�ȕK�v�͂Ȃ��B��������ˑ��R���|�[�l���g�Ƃ��Ĉ����A�e�X�g�ΏۃR�[�h��
 * �j�[�Y�ɂ҂����荇�����C���^�[�t�F�[�X���`����΂����̂��B�C���^�[�t�F�C�X�����邨�����ŁA��������
 * ���m�Ȃ���̂Ƃ̈ˑ��֌W��f���؂鎖���ł���B���m�Ȃ���̂ɋ��߂邱�Ƃ��C���^�[�t�F�C�X�Ƃ���
 * ��`���邱�ƂŁA�������͂��̂��Ԃ��΂܂ŊJ���ł���̂��B���̂Ƃ��A�e�X�g��
 * �݌v���쓮���鏕���ɂȂ��Ă����B
 * �@�ڍׂ��܂��S���킩��Ȃ��Ƃ��Ƀv���O���~���O���邱�Ƃ́A�჌�x���̎����ڍׂɉ�������Ă��Ȃ����ۓI��
 * �C���^�[�t�F�C�X�ɂȂ�₷���B�����ł͎����𖾂炩�ɂ��Ă��Ȃ����߁A�ʂ̃^�[�Q�b�g�����ɈقȂ������
 * �p�ӂ��邱�Ƃ��\���B
 * �@�����ł͐V�����t�F�C�N���쓮���邽�߂̃e�X�g�������̂����A�V�����t�F�C�N�����삷�邱�Ƃ��m���߂邽�߂ł͂Ȃ��A
 * �ނ���t�F�C�N�̐U�镑�����h�L�������g�����邽�߂��B
 */TEST(LightSchedule, Create) {
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightSchedule, RememberTheLastLightIdControlled) {
	LightController_On(10);
	checkLightState(10, LIGHT_ON);
}

//Schedule�C�x���g���������Ȃ��P�[�X����e�X�g������
TEST(LightSchedule, NoScheduleNothingHappens) {
	setTimeTo(MONDAY, 100);
	LightScheduler_Wakeup();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

//����Schedule�C�x���g����������P�[�X������
//�ŏ��ɂ������R�����g�A�E�g���Ă����e�X�g�P�[�X��L���ɂ���B
TEST(LightSchedule, ScheduleOnEverydatyNotTimeYet) {
	/*
	 * LightScheduler���e�X�g���邽�߂ɕK�v��LightControllerSpy��FakeTimeService��
	 * �������l����̂ɖ𗧂e�X�g�P�[�X��������(�}8-4�@���C�g�X�P�W���[���@�\�̃��j�b�g�e�X�g�\�����Q�Ɓj
	 */
	//����(Everyday)�A1200����(�ߌ�8���j��ID���R�̃��C�g���I���ɂ���悤�X�P�W���[������B
	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
	//���Ɏ��v���R���g���[�����āA���j���̌ߌ�7��59��(1199����)�ɃZ�b�g����FakeTimeService�Ɏw�����Ă���B
	setTimeTo(MONDAY, 1199);

	/*
	 * Execute
	 */
	//�v���_�N�g�R�[�h��TimeService(�}8-4�Q�Ɓj����������Ă���悤�ɁA
	//LightScheduler_Wakeup()�̃R�[���o�b�N���V�~�����[�g����B
	LightScheduler_Wakeup();

	/*
	 * Verify
	 */
	//MONDAY, 1199���ڂ̓X�P�W���[�����ꂽ�����ł͂Ȃ����߁ALightController�̊֐��͌Ăяo����Ȃ��͂�(xxx_UNKNOWN���ԋp�����͂��j�B
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightSchedule, ScheduleOnEverydayItsTime) {
	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

	setTimeTo(MONDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_ON);
}

TEST(LightSchedule, ScheduleOffEventdayItsTime) {
	LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);

	setTimeTo(MONDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_OFF);
}

TEST(LightSchedule, ScheduleTuesdayButItsMonday) {
	LightScheduler_ScheduleTurnOff(3, TUESDAY, 1200);

	setTimeTo(MONDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightSchedule, ScheduleTuesdayAndItsThuesday) {
	LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);

	setTimeTo(TUESDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_ON);
}

TEST(LightSchedule, ScheduleWeekEndItsFriday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

	setTimeTo(FRIDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightSchedule, ScheduleWeekEndItsSaturday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

	setTimeTo(SATURDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_ON);
}

TEST(LightSchedule, ScheduleWeekEndItsSunday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

	setTimeTo(SUNDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_ON);
}

TEST(LightSchedule, ScheduleWeekEndItsMonday) {
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);

	setTimeTo(MONDAY, 1200);

	LightScheduler_Wakeup();

	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

/*
 * �������ƃN���[���i�b�v�̃e�X�g�́A����LightScheduler�̎�R�Ƃ͂��Ȃ����Ă���̂�
 * �V����TEST_GROUP��ǉ������B
 */TEST_GROUP(LightSchedulerInitAndCleanup) {

};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm) {
	LightSchedule_Create();
	POINTERS_EQUAL((void * )LightScheduler_Wakeup,
			(void * )FakeTimeService_GetAlarmCallback());
	LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
	LightSchedule_Destroy();
}

/*
 * ����Light�̐���
 */TEST_GROUP(LightControllerSpy) {

	void setup() {
		LightSchedule_Create();
		LightController_Create();
	}

	void teardown() {
		LightSchedule_Destroy();
		LightController_Destroy();
	}

	void checkLightState(int id, int level) {
		if (id == LIGHT_ID_UNKNOWN) {
			LONGS_EQUAL(id, LightControllerSpy_GetLastID());
			LONGS_EQUAL(level, LightControllerSpy_GetLastState());
		} else {
			LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
		}
	}
};

TEST(LightControllerSpy, RememberAllLightStates) {
	LightController_On(0);
	LightController_Off(31);
	checkLightState(0, LIGHT_ON);
	checkLightState(31, LIGHT_OFF);
}

TEST(LightControllerSpy, ScheduleTwoEventsAtTheSameTime) {
	LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
	LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

	FakeTimeService_SetMinute(1200);
	FakeTimeService_SetDay(SUNDAY);

	LightScheduler_Wakeup();

	checkLightState(3, LIGHT_ON);
	checkLightState(12, LIGHT_ON);
}

TEST(LightControllerSpy, RejectsTooManyEvents) {
	int i;
	for (i = 0; i < 128; i++)
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

	LONGS_EQUAL(LS_TOO_MANY_EVENTS,
			LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));
}

TEST(LightControllerSpy, RemoveRecyclesScheduleSlot) {
	int i;
	for (i = 0; i < 128; i++)
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + i));

	LightScheduler_ScheduleRemove(6, MONDAY, 600);
	LONGS_EQUAL(LS_OK,
			LightScheduler_ScheduleTurnOn(13, MONDAY, 600 + i));
}

TEST(LightSchedule, RemoveMultipleScheduledEvent) {
	LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
	LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
	LightScheduler_ScheduleRemove(6, MONDAY, 600);

	setTimeTo(MONDAY, 600);

	LightScheduler_Wakeup();

	checkLightState(6, LIGHT_STATE_UNKNOWN);
	checkLightState(7, LIGHT_ON);

}

TEST(LightSchedule, AcceptsValidLightIds) {
	LONGS_EQUAL(LS_OK,LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
	LONGS_EQUAL(LS_OK,LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
	LONGS_EQUAL(LS_OK,LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightSchedule, RejectsInvalidLightIds) {
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}
