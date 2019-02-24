#include "Result.h"
#include "Game.h"
#include "DxLib.h"

Result::Result() : BaseScene() {



}
Result::~Result() {

}
void Result::Initialize() {
	if (clear_flag[CSelectNum][DSelectNum] == 1) {
		mImageHandle = LoadGraph("画像/画面/クリア.png");
	}
	else {
		mImageHandle = LoadGraph("画像/画面/非クリア.png");
	}
	
	mSoundHandle = LoadSoundMem("音/曲決定.wav");

	Jacketimg[0] = LoadGraph("画像/ジャケット/selectA.png");
	Jacketimg[1] = LoadGraph("画像/ジャケット/hellnear.png");
	Jacketimg[2] = LoadGraph("画像/ジャケット/unequald_j.png");
	Jacketimg[3] = LoadGraph("画像/ジャケット/selectD.png");
	Jacketimg[4] = LoadGraph("画像/ジャケット/select2.png");

	Otherimg[0] = LoadGraph("画像/画面/select2.png");
	Otherimg[1] = LoadGraph("画像/画面/select2yellow.png");
	Otherimg[2] = LoadGraph("画像/画面/select2red.png");
	Otherimg[3] = LoadGraph("画像/画面/select2black.png");
	Otherimg[4] = LoadGraph("画像/画面/part.png");
	Otherimg[5] = LoadGraph("画像/画面/part2.png");

	drawcount = 100;

}
void Result::Finalize() {
	DeleteGraph(mImageHandle);
	DeleteGraph(mSoundHandle);
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	for (int i = 0; i < 9; i++) {
		DeleteGraph(Otherimg[i]);
	}
}
void Result::Update() {
	if (counter < 255 && fade_flag == false) {  //最初のフェードイン
												//	SetDrawBright(counter, counter, counter);でもおｋ
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //切り替わりのフェードアウト

		counter = counter - 5;
	}

	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		StopSoundMem(Music[1]);
		fade_flag = true;	
	}
	
	if (counter == 0 && fade_flag == true) { //ここでフェードアウトで真っ暗のときにシーンを替える
		BaseScene::NowScene = eScene::eScene_Select;
	}

	if (drawcount > 0) {
		drawcount--;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //すべてを終える
		exit(1);
	}

}

//描画
void Result::Draw() {
	BaseScene::Draw();

	DrawRotaGraph(500, 500, 0.6, 0.0, Otherimg[DSelectNum], TRUE);
	DrawRotaGraph(500, 500, 0.4, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();
	SetFontSize(256);
	tennmetu++;
	//if (tennmetu % 2 == 1) {
		if (drawcount < 100) {
			DrawRotaGraph3(1000, 200, 0, 0, 1.0, 0.1, 0.0, Otherimg[0], TRUE);
			if (drawcount < 90) {
				DrawRotaGraph3(900, 450, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
				if (drawcount < 80) {
					DrawRotaGraph3(900, 600, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
					if (drawcount < 70) {
						DrawRotaGraph3(900, 750, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
						if (drawcount < 50) {
							DrawRotaGraph3(-300, 400, 0, 0, 1.0, 1.0, 0.0, Otherimg[5], TRUE);
							
							if (drawcount == 0) {
								DrawRotaGraph3(1300, 750, 0, 0, 0.3, 0.3, 0.0, Otherimg[0], TRUE);
								if (score[CSelectNum][DSelectNum] >= 950000) {
									DrawString(1425, 800, "S", GetColor(255, 255, 0));
								}
								else if (score[CSelectNum][DSelectNum] >= 900000) {
									DrawString(1425, 800, "A", GetColor(255, 255, 0));
								}
								else if (score[CSelectNum][DSelectNum] >= 800000) {
									DrawString(1425, 800, "B", GetColor(130, 130, 130));
								}
								else {
									DrawString(1425, 800, "C", GetColor(150, 100, 0));
								}
								if (clear_flag[CSelectNum][DSelectNum] == 1) {
									DrawString(300, 850, "CLEAR", GetColor(130, 130, 255));
								}
								else {
									DrawString(300, 850, "FAIL", GetColor(255, 130, 130));
								}
							}
						}
					}
				}
			}
		}
	//}
	
	SetFontSize(32);
	
	if (drawcount < 100) {
		
		if (drawcount < 90) {
			DrawString(1000, 470, "GREAT", GetColor(120, 120, 255));
			DrawFormatString(1200, 470, 0xffffff, "%d", great_count);
			if (drawcount < 80) {
				DrawString(1000, 620, "GOOD", GetColor(255, 120, 80));
				DrawFormatString(1200, 620, 0xffffff, "%d", ok_count);
				if (drawcount < 70) {
					DrawString(1000, 770, "BAD", GetColor(255, 80, 120));
					DrawString(1450, 900, "RANK", GetColor(130, 130, 255));
					DrawFormatString(1200, 770, 0xffffff, "%d", bad_count);
					if (drawcount == 0) {

					}
				}
			}
		}
	}
	SetFontSize(64);
	if (drawcount < 70) {
		DrawString(1000, 220, "SCORE", GetColor(255, 80, 120));
		DrawFormatString(1400, 250, 0xffffff, "%d", score[CSelectNum][DSelectNum]);
		if (drawcount == 0) {

		}
	}
	SelectDif[DSelectNum].Draw();
	
	//新記録の上書き
	if (highscore[CSelectNum][DSelectNum] < score[CSelectNum][DSelectNum]) {
		highscore[CSelectNum][DSelectNum] = score[CSelectNum][DSelectNum];
	}
	

	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}