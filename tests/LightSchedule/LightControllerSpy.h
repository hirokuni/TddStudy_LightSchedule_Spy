/*
 * LightControllerSpy.h
 *
 *  Created on: 2013/06/23
 *      Author: hirokuni
 */

#ifndef LIGHTCONTROLLERSPY_H_
#define LIGHTCONTROLLERSPY_H_

#include "LightController.h"

//�Ȃ��X�p�C�w�b�_�ɉ��L�̃��C�g��Ԃ��`���Ă��邩�Ƃ����ƁA
//�����̃��e�����l�́A�e�X�g���ɃX�p�C�ɖ₢���킹�邽�߂Ɏg������̂��B
//�������v���_�N�g�R�[�h�ɓ���ăv���_�N�g�R�[�h����������K�v�͂Ȃ����낤�B
enum
{
	LIGHT_ID_UNKNOWN = 1,
	LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0,
	LIGHT_ON = 1
};

int LightControllerSpy_GetLastID(void);
int LightControllerSpy_GetLastState(void);

#endif /* LIGHTCONTROLLERSPY_H_ */
