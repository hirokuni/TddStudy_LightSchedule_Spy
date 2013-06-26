/*
 * LightControllerSpy.h
 *
 *  Created on: 2013/06/23
 *      Author: hirokuni
 */

#ifndef LIGHTCONTROLLERSPY_H_
#define LIGHTCONTROLLERSPY_H_

#include "LightController.h"

//なぜスパイヘッダに下記のライト状態を定義しているかというと、
//これらのリテラル値は、テスト中にスパイに問い合わせるために使われるものだ。
//これらをプロダクトコードに入れてプロダクトコードを汚染する必要はないだろう。
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
