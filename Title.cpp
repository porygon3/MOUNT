#include "Title.h"
#include "DxLib.h"

Title::Title() : BaseScene() {


}
Title::~Title() {}

//初期化
void Title::Initialize() {
	mImageHandle = LoadGraph("画像/画面/title.png");
}

void Title::Finalize() {
	DeleteGraph(mImageHandle);
}

//更新
void Title::Update() {
	if (counter < 255 && fade_flag == false) {  //最初のフェードイン
	//	
		(counter, counter, counter);
		counter=counter+5;
	}
	else if (counter > 0 && fade_flag == true) { //切り替わりのフェードアウト
		counter=counter-5;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		fade_flag = true;
	}

	if (counter == 0 && fade_flag == true) { //ここでフェードアウトで真っ暗のときにシーンを替える
		BaseScene::NowScene = eScene::eScene_Select;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //すべてを終える
		exit(1);
	}
}

//描画
void Title::Draw() {
	
	BaseScene::Draw();
	DrawString(40, 700, "EXIT [ESC]", GetColor(255, 255, 255));
	DrawString(800, 800, "- PUSH ENTER -", GetColor(255, 255, 255));
	SetFontSize(32);
	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}