#include "Jacket.h"
#include "DxLib.h"

Jacket::Jacket() :BaseScene() {
	
}
Jacket::~Jacket() {

}

//初期化
void Jacket::Initialize() {
	mImageHandle = LoadGraph("画像/画面/game.png");
	mSoundHandle = LoadSoundMem("音/曲決定.wav");

	Jacketimg[0] = LoadGraph("画像/ジャケット/selectA.png");
	Jacketimg[1] = LoadGraph("画像/ジャケット/hellnear.png");
	Jacketimg[2] = LoadGraph("画像/ジャケット/unequald_j.png");
	Jacketimg[3] = LoadGraph("画像/ジャケット/selectD.png");
	Jacketimg[4] = LoadGraph("画像/ジャケット/select2.png");
	Jacketimg[5] = LoadGraph("画像/ジャケット/select2.png");

	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
}
//ここに選曲画面と共有するCSelectNum

void Jacket::Finalize(){
	DeleteGraph(mImageHandle);
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	DeleteSoundMem(mSoundHandle);
}

//更新
void Jacket::Update() {
	if (counter < 255 && fade_flag == false) {  //最初のフェードイン
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //切り替わりのフェードアウト
		counter = counter - 5; 
	}


	if (counter > 254) {
		WaitTimer(700);
		fade_flag = true;
	}

	if (counter == 0 && fade_flag == true) { //ここでフェードアウトで真っ暗のときにシーンを替える
		BaseScene::NowScene = eScene::eScene_Game;
	}
}

//描画
void Jacket::Draw() {
	BaseScene::Draw();
	DrawRotaGraph(960, 500, 0.6, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();
	SelectDif[DSelectNum].Draw();

	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}