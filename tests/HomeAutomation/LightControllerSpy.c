/*
 * LightControllerSpy.c
 *
 *  Created on: 2013/06/23
 *      Author: hirokuni
 */


#include "LightSchedule/LightControllerSpy.h"


// デッドドロップを定義。（「デッドドロップ」とはスパイが情報を受け渡しする秘密の場所のこと）
static int lastId;
static int lastState;

void LightController_Create(void) {
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}


void LightController_Destroy(void){

}

// スパイは作戦中、置き換えたコラボレータのインターフェイス(図8-4 「LightController」 interfaceの事。ここでは下記
// 「LightController_On」、「LightController_Off」がプロダクトコードの実装の代わりにリンカにより置き換えられてテスト中に使用される)を通して機密情報(on または off を要求されるLightのID)を傍受する。
void LightController_On(int id) {
	lastId = id;
	lastState = LIGHT_ON;
}

void LightController_Off(int id) {
	lastId = id;
	lastState = LIGHT_OFF;
}

//　テスト対象コードを動かすと、秘密のアクセサ関数を通してデッドドロップから機密情報が取得できる。
int LightControllerSpy_GetLastID(void) {
	return lastId;
}

int LightControllerSpy_GetLastState(void) {
	return lastState;
}
