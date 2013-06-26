/*
 * LightControllerSpy.c
 *
 *  Created on: 2013/06/23
 *      Author: hirokuni
 */


#include "LightSchedule/LightControllerSpy.h"


// �f�b�h�h���b�v���`�B�i�u�f�b�h�h���b�v�v�Ƃ̓X�p�C�������󂯓n������閧�̏ꏊ�̂��Ɓj
static int lastId;
static int lastState;

void LightController_Create(void) {
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}


void LightController_Destroy(void){

}

// �X�p�C�͍�풆�A�u���������R���{���[�^�̃C���^�[�t�F�C�X(�}8-4 �uLightController�v interface�̎��B�����ł͉��L
// �uLightController_On�v�A�uLightController_Off�v���v���_�N�g�R�[�h�̎����̑���Ƀ����J�ɂ��u���������ăe�X�g���Ɏg�p�����)��ʂ��ċ@�����(on �܂��� off ��v�������Light��ID)��T�󂷂�B
void LightController_On(int id) {
	lastId = id;
	lastState = LIGHT_ON;
}

void LightController_Off(int id) {
	lastId = id;
	lastState = LIGHT_OFF;
}

//�@�e�X�g�ΏۃR�[�h�𓮂����ƁA�閧�̃A�N�Z�T�֐���ʂ��ăf�b�h�h���b�v����@����񂪎擾�ł���B
int LightControllerSpy_GetLastID(void) {
	return lastId;
}

int LightControllerSpy_GetLastState(void) {
	return lastState;
}