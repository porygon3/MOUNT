#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(1920,1080, 32);
	ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr* sm = new SceneMgr();
	

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {  //画面更新、メッセージ更新、画面消去
		Keyboard::Update();
		sm->Update();    //更新
		sm->Draw();    //描写
		
	}
	delete sm;

	DxLib_End();
	return 0;
}