extern "C" {
#include "LightSchedule.h"
#include "LightControllerSpy.h"
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

/*
 *  最初のテストとしてぴったりなのは、次のように初期化中に何が起こるべきかを明確にするテストだろう。
 * このテストは簡単に組み立てられるし、フィードバックもすぐに得られる。LightSchedulerには
 * 何も必要ないので、テストダブルの準備に集中できる。
 *  もしOSをまだ選定していなかったり、ライトをコントロールするはーどうぇあがまだ計画段階であれば、どうする？
 * それらが決まるまで実装を止めなくてはならないのか？
 * 	もちろんそんな必要はない。これら二つを依存コンポーネントとして扱い、テスト対象コードの
 * ニーズにぴったり合ったインターフェースを定義すればいいのだ。インターフェイスがあるおかげで、私たちは
 * 未知なるものとの依存関係を断ち切る事ができる。未知なるものに求めることをインターフェイスとして
 * 定義することで、私たちはそのすぶそばまで開発できるのだ。このとき、テストは
 * 設計を駆動する助けになってくれる。
 * 　詳細がまだ全部わからないときにプログラミングすることは、低レベルの実装詳細に汚染されていない抽象的な
 * インターフェイスになりやすい。ここでは実装を明らかにしていないため、別のターゲット向けに異なる実装を
 * 用意することも可能だ。
 * 　ここでは新しいフェイクを駆動するためのテストを書くのだが、新しいフェイクが動作することを確かめるためではなく、
 * むしろフェイクの振る舞いをドキュメント化するためだ。
 */
TEST(LightSchedule, Create) {
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastID());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightSchedule, RememberTheLastLightIdControlled) {
	LightController_On(10);
	LONGS_EQUAL(10, LightControllerSpy_GetLastID());
	LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}
