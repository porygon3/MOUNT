#include "DxLib.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetGraphMode(1920,1080, 32);
	ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr* sm = new SceneMgr();
	

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {  //��ʍX�V�A���b�Z�[�W�X�V�A��ʏ���
		Keyboard::Update();
		sm->Update();    //�X�V
		sm->Draw();    //�`��
		
	}
	delete sm;

	DxLib_End();
	return 0;
}