extern "C" {
#include "LightSchedule.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightSchedule) {
	void setup() {
		LightSchedule_Create();
	}

	void teardown() {
		LightSchedule_Destroy();
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
