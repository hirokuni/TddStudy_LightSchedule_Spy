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
 * 最初のテストにしては下記のコードは大きすぎる。このテストを実施するには、二つのテストダブル(FakeTimeService、LightController spy)と
 * プロダクトコードのスケルトン実装を各必要がある。しかも、これらすべてのピースをうまく組み合わせなければ成らない。とりあえずこのテストを
 * コメントアウトする。
 */
//TEST(LightSchedule, ScheduleOnEverydatyNotTimeYet) {
//	/*
//	 * LightSchedulerをテストするために必要なLightControllerSpyとFakeTimeServiceの
//	 * 役割を考えるのに役立つテストケースを書こう(図8-4　ライトスケジュール機能のユニットテスト構造を参照）
//	 */
//	//毎日(Everyday)、1200分目(午後8時）にIDが３のライトをオンにするようスケジュールする。
//	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
//	//次に時計をコントロールして、月曜日の午後7時59分(1199分目)にセットするFakeTimeServiceに指示している。
//	FakeTimeService_SetDay (MONDAY);
//	FakeTimeService_SetMinute(1199);
//
//	/*
//	 * Execute
//	 */
//	//プロダクトコードのTimeService(図8-4参照）が毎分やっているように、
//	//LightScheduler_Wakeup()のコールバックをシミュレートする。
//	LightScheduler_Wakeup();
//
//	/*
//	 * Verify
//	 */
//	//MONDAY, 1199分目はスケジュールされた期限ではないため、LightControllerの関数は呼び出されないはず(xxx_UNKNOWNが返却されるはず）。
//	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
//	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
//
//}
