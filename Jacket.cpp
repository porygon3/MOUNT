#include "Jacket.h"
#include "DxLib.h"

//コンストラクタ--------------------------------------------------------------------------
Jacket::Jacket() :BaseScene() {
	Initialize();

	SelectTitle[0].SMake(700, 900, 280, "ハイスピ2000", 1, 2, 4, 6);  //5つの構造体に中身を与える
	SelectTitle[1].SMake(700, 900, 160, "Heaven helps you", 1, 3, 5, 7);
	SelectTitle[2].SMake(700, 900, 250, "UN Equald", 3, 5, 7, 9);
	SelectTitle[3].SMake(700, 900, 178, "Gear", 2, 4, 6, 8);
	SelectTitle[4].SMake(700, 900, 165, "INVASION", 3, 5, 7, 10);
	SelectTitle[5].SMake(700, 900, 0, "----------EXIT----------", 0, 0, 0, 0);

	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
	
}
//デストラクタ--------------------------------------------------------------------------
Jacket::~Jacket() {
	Finalize();
}

//初期化--------------------------------------------------------------------------
void Jacket::Initialize() {
	mImageHandle = LoadGraph("画像/画面/jacket.png");
	mSoundHandle = LoadSoundMem("音/曲決定.wav");

	Jacketimg[0] = LoadGraph("画像/ジャケット/RH.png");
	Jacketimg[1] = LoadGraph("画像/ジャケット/hellnear.png");
	Jacketimg[2] = LoadGraph("画像/ジャケット/unequald_j.png");
	Jacketimg[3] = LoadGraph("画像/ジャケット/darkRL.png");
	Jacketimg[4] = LoadGraph("画像/ジャケット/invasion.png");
	Jacketimg[5] = 0;

	timer = 100;
}

//メモリ開放--------------------------------------------------------------------------
void Jacket::Finalize(){
	DeleteGraph(mImageHandle);
	for (int i = 0; i < SelectNum; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	DeleteSoundMem(mSoundHandle);
}

//更新--------------------------------------------------------------------------
void Jacket::Update() {
	if (counter < Illum && fade_flag == false) {  //最初のフェードイン
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //切り替わりのフェードアウト
		counter = counter - 5; 
	}

	if (counter > Illum - 1) {
		if (timer > 0) {
			timer--;
		}
		else {
			fade_flag = true;
		}
	}

	if (counter == 0 && fade_flag == true) { //ここでフェードアウトで真っ暗のときにシーンを替える
		BaseScene::NowScene = eScene::eScene_Game;
	}
}

//描画--------------------------------------------------------------------------
void Jacket::Draw() {
	BaseScene::Draw();
	DrawRotaGraph(960, 500, 0.6, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();
	SelectDif[DSelectNum].Draw();

	DrawString(1300, 900, "BPM", GetColor(255, 120, 255));
	DrawFormatString(1375, 900, 0xffffff, "%d", SelectTitle[CSelectNum].bpm);

	Fadeout();
}