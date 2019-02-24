#include "Game.h"
#include "DxLib.h"
#include <stdio.h>
#include <deque>

#include <fstream>
#include <iostream>
#include <string>

Game::Game() : BaseScene() {

	std::string text_name;
	text_name = "譜面/test"+std::to_string(CSelectNum)+"," + std::to_string(DSelectNum) + ".txt";


	//ファイル読み込み
	std::ifstream n_file(text_name);
	std::string str;


	getline(n_file, str); //タイトルなどを読み込み
	f_title = str;
	getline(n_file, str);
	f_bpm = str;
	BPM = std::stoi(f_bpm);
	getline(n_file, str);
	f_beat = str;
	Beat = std::stoi(f_beat);
	getline(n_file, str);
	f_speed = str;
	Speed = std::stoi(f_speed);
	
	notescount = 0;
	int Y_num = 0;
	while (getline(n_file, str)) {
		for (int i = 0; i < 5; i++) {

			if (str[i] != '0') {
				Notes[i].push_back(NotesBase());	//0のとき、何もない空で間を埋める。

				switch (str[i]) {
				case '1':
					//Notes[i][(signed)Notes[i].size() - 1].Init(711 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 1);    リファレンスによって座標が違う
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 1);
					//((60.0 / BPM) / Beat)
					break;
				case '2':
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 2);
					break;
				case '3':
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 3);
					break;
				case '4':
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 4);
					break;
				case '5':
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 5);
					break;
				case '6':
					Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 6);
					break;
				default:
					break;
				}
				if (i < 4) {
					notescount++;
				}

			}
		}
		Y_num++;
	}
	for (int j = 0; j < Notes.size(); j++) {Notes[j].resize(Notes[j].size() + 1);}
}
Game::~Game() {
	
}


//初期化
void Game::Initialize() {
	mImageHandle = LoadGraph("画像/画面/start.png");

	Otherimg[0] = LoadGraph("画像/画面/譜面.png");
	Otherimg[1] = LoadGraph("画像/画面/バックライト1.png");
	Otherimg[2] = LoadGraph("画像/画面/判定線.png");
	Otherimg[3] = LoadGraph("画像/画面/キーライト.png");
	Otherimg[4] = LoadGraph("画像/画面/ゲージ赤.png");
	Otherimg[5] = LoadGraph("画像/画面/ゲージ青.png");
	Otherimg[6] = LoadGraph("画像/画面/ゲージケース.png");
	Otherimg[7] = LoadGraph("画像/画面/unit2.png");
	Otherimg[8] = LoadGraph("画像/画面/unitflash.png");
	Otherimg[9] = LoadGraph("画像/画面/select2.png");

	Notesimg[0] = LoadGraph("画像/Notes/ノーツ1.png");
	Notesimg[1] = LoadGraph("画像/Notes/ノーツ2.png");
	Notesimg[2] = LoadGraph("画像/Notes/ノーツ3.png");
	Notesimg[3] = LoadGraph("画像/Notes/ロングノーツ1.png");
	Notesimg[4] = LoadGraph("画像/Notes/ロングノーツ2.png");
	Notesimg[5] = LoadGraph("画像/Notes/ロングノーツ3.png");

	Jacketimg[0] = LoadGraph("画像/ジャケット/selectA.png");
	Jacketimg[1] = LoadGraph("画像/ジャケット/hellnear.png");
	Jacketimg[2] = LoadGraph("画像/ジャケット/unequald_j.png");
	Jacketimg[3] = LoadGraph("画像/ジャケット/selectD.png");
	Jacketimg[4] = LoadGraph("画像/ジャケット/select2.png");
	Jacketimg[5] = LoadGraph("画像/ジャケット/select2.png");
	
	Music[1] = LoadSoundMem("音/曲/ﾕｳﾃﾗｳﾁ（声もﾕｳﾃﾗｳﾁ）.wav");

	NowTime = 0.0;
	OldTime = 0.0;

	starttime = 200;
	endtime = 200;

	rightcount = 255;
	for (int i = 0; i < 4; i++) {
		keyrightcount[i] = 255;
		judge_great[i] = 0, judge_ok[i] = 0, judge_bad[i] = 0;
	}

	combo = 0,combocount = 0;
	
	gaugecount = 0.0;
}

void Game::Finalize() {
	//画像削除
	DeleteGraph(mImageHandle);
	for (int i = 0; i < 5; i++) {
		DeleteGraph(Notesimg[i]);
	}
	for (int i = 0; i < 9; i++) {
		DeleteGraph(Otherimg[i]);
	}
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Jacketimg[i]);
	}


	//ノーツ削除
	Notes[0].clear();
	Notes[0].shrink_to_fit();
}

//更新
void Game::Update() {
	if (counter < 255 && fade_flag == false) {  //最初のフェードイン
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
		BaseScene::NowScene = eScene::eScene_Result;
	}

	
	if (rightcount > 0) { 
		rightcount = rightcount - 15;
	}
	for (int i = 0; i < 4; i++) {
		if (keyrightcount[i] > 0) {
			keyrightcount[i] = keyrightcount[i] - 15;
		}
		judge_great[i]--;
		judge_ok[i]--;
		judge_bad[i]--;
	}

	if (start_flag == true) {
		StartTime = GetNowHiPerformanceCount();
		OldTime = StartTime;

		start_flag = false;
	}
	else {
		OldTime = NowTime;
	}


	NowTime = GetNowHiPerformanceCount();
	difference = (double)(NowTime - OldTime);

	
	//落とす処理
	if (starttime == 0) {
		for (int i = 0, n = (signed)Notes.size(); i < n; i++) {
			if (!Notes[i].empty()) {
				for (int j = 0, m = Notes[i].size(); j < m; j++) {
					Notes[i][j].Down(difference, Speed);
				}
			}
		}
	}
	if (starttime > 0) {
		starttime--;
	}
	//終了判定
	if (endtime == 0) {
		fade_flag = true;
	}
	if (end_flag == true) {
		endtime--;
	}


	//判定
	if (Notes[0][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_V) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 896.0 - (Speed / 100) && Notes[0][0].y <= 976.0 + (Speed / 100)) {
					Ok(0);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 876.0 - (Speed / 100) && Notes[0][0].y <= 996.0 + (Speed / 100)) {
					Bad(0);
					Linedelete(0);
				}
			}
		}
	}
	else if (Notes[0][0].NotesColor == 2){
		if (Keyboard::GetKey(KEY_INPUT_F) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 896.0 - (Speed / 100) && Notes[0][0].y <= 976.0 + (Speed / 100)) {
					Ok(0);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 876.0 - (Speed / 100) && Notes[0][0].y <= 996.0 + (Speed / 100)) {
					Bad(0);
					Linedelete(0);
				}
			}
		}
	}
	else if (Notes[0][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_R) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 896.0 - (Speed / 100) && Notes[0][0].y <= 976.0 + (Speed / 100)) {
					Ok(0);
					Linedelete(0);
				}
				else if (Notes[0][0].y >= 876.0 - (Speed / 100) && Notes[0][0].y <= 996.0 + (Speed / 100)) {
					Bad(0);
					Linedelete(0);
				}
			}
		}
	}
	else if (Notes[0][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_V) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
			}
		}
	}
	else if (Notes[0][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_F) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
			}
		}
	}
	else if (Notes[0][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_R) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[0][0].y >= 916.0 - (Speed / 100) && Notes[0][0].y <= 956.0 + (Speed / 100)) {
					Great(0,Notes[0][0].NotesColor);
					Linedelete(0);
				}
			}
		}
	}


	if (Notes[1][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_B) == 1) { //G
			if (!Notes[1].empty()) {
				if (Notes[1][0].y >= 916 - (Speed / 100) && Notes[1][0].y <= 956 + (Speed / 100) && Notes[1][0].NotesColor == 1) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 896.0 - (Speed / 100) && Notes[1][0].y <= 976.0 + (Speed / 100)) {
					Ok(1);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 876.0 - (Speed / 100) && Notes[1][0].y <= 996.0 + (Speed / 100)) {
					Bad(1);
					Linedelete(1);
				}
			}
		}
	}
	else if (Notes[1][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_G) == 1) { //G
			if (!Notes[1].empty()) {
				if (Notes[1][0].y >= 916 - (Speed / 100) && Notes[1][0].y <= 956 + (Speed / 100) && Notes[1][0].NotesColor == 1) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 896.0 - (Speed / 100) && Notes[1][0].y <= 976.0 + (Speed / 100)) {
					Ok(1);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 876.0 - (Speed / 100) && Notes[1][0].y <= 996.0 + (Speed / 100)) {
					Bad(1);
					Linedelete(1);
				}
			}
		}
	}
	else if (Notes[1][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_T) == 1) { //G
			if (!Notes[1].empty()) {
				if (Notes[1][0].y >= 916 - (Speed / 100) && Notes[1][0].y <= 956 + (Speed / 100) && Notes[1][0].NotesColor == 1) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 896.0 - (Speed / 100) && Notes[1][0].y <= 976.0 + (Speed / 100)) {
					Ok(1);
					Linedelete(1);
				}
				else if (Notes[1][0].y >= 876.0 - (Speed / 100) && Notes[1][0].y <= 996.0 + (Speed / 100)) {
					Bad(1);
					Linedelete(1);
				}
			}
		}
	}
	else if (Notes[1][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_B) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[1][0].y >= 916.0 - (Speed / 100) && Notes[1][0].y <= 956.0 + (Speed / 100)) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(1);
				}
			}
		}
	}
	else if (Notes[1][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_G) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[1][0].y >= 916.0 - (Speed / 100) && Notes[1][0].y <= 956.0 + (Speed / 100)) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(1);
				}
			}
		}
	}
	else if (Notes[1][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_T) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[1][0].y >= 916.0 - (Speed / 100) && Notes[1][0].y <= 956.0 + (Speed / 100)) {
					Great(1,Notes[1][0].NotesColor);
					Linedelete(0);
				}
			}
		}
	}

	if (Notes[2][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_N) == 1) { //H
			if (!Notes[2].empty()) {
				if (Notes[2][0].y >= 916 - (Speed / 100) && Notes[2][0].y <= 956 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 896.0 - (Speed / 100) && Notes[2][0].y <= 976.0 + (Speed / 100)) {
					Ok(2);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 876.0 - (Speed / 100) && Notes[2][0].y <= 996.0 + (Speed / 100)) {
					Bad(2);
					Linedelete(2);
				}
			}
		}
	}
	else if (Notes[2][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_H) == 1) { //H
			if (!Notes[2].empty()) {
				if (Notes[2][0].y >= 916 - (Speed / 100) && Notes[2][0].y <= 956 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 896.0 - (Speed / 100) && Notes[2][0].y <= 976.0 + (Speed / 100)) {
					Ok(2);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 876.0 - (Speed / 100) && Notes[2][0].y <= 996.0 + (Speed / 100)) {
					Bad(2);
					Linedelete(2);
				}
			}
		}
	}
	else if (Notes[2][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_Y) == 1) { //H
			if (!Notes[2].empty()) {
				if (Notes[2][0].y >= 916 - (Speed / 100) && Notes[2][0].y <= 956 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 896.0 - (Speed / 100) && Notes[2][0].y <= 976.0 + (Speed / 100)) {
					Ok(2);
					Linedelete(2);
				}
				else if (Notes[2][0].y >= 876.0 - (Speed / 100) && Notes[2][0].y <= 996.0 + (Speed / 100)) {
					Bad(2);
					Linedelete(2);
				}
			}
		}
	}
	else if (Notes[2][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_N) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[2][0].y >= 916.0 - (Speed / 100) && Notes[2][0].y <= 956.0 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
			}
		}
	}
	else if (Notes[2][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_H) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[2][0].y >= 916.0 - (Speed / 100) && Notes[2][0].y <= 956.0 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
			}
		}
	}
	else if (Notes[2][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_Y) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[2][0].y >= 916.0 - (Speed / 100) && Notes[2][0].y <= 956.0 + (Speed / 100)) {
					Great(2,Notes[2][0].NotesColor);
					Linedelete(2);
				}
			}
		}
	}

	if (Notes[3][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_M) == 1) { //H
			if (!Notes[3].empty()) {
				if (Notes[3][0].y >= 916 - (Speed / 100) && Notes[3][0].y <= 956 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 896.0 - (Speed / 100) && Notes[3][0].y <= 976.0 + (Speed / 100)) {
					Ok(3);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 876.0 - (Speed / 100) && Notes[3][0].y <= 996.0 + (Speed / 100)) {
					Bad(3);
					Linedelete(3);
				}
			}
		}
	}
	else if (Notes[3][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_J) == 1) { //H
			if (!Notes[3].empty()) {
				if (Notes[3][0].y >= 916 - (Speed / 100) && Notes[3][0].y <= 956 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 896.0 - (Speed / 100) && Notes[3][0].y <= 976.0 + (Speed / 100)) {
					Ok(3);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 876.0 - (Speed / 100) && Notes[3][0].y <= 996.0 + (Speed / 100)) {
					Bad(3);
					Linedelete(3);
				}
			}
		}
	}
	else if (Notes[3][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_U) == 1) { //H
			if (!Notes[3].empty()) {
				if (Notes[3][0].y >= 916 - (Speed / 100) && Notes[3][0].y <= 956 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 896.0 - (Speed / 100) && Notes[3][0].y <= 976.0 + (Speed / 100)) {
					Ok(3);
					Linedelete(3);
				}
				else if (Notes[3][0].y >= 876.0 - (Speed / 100) && Notes[3][0].y <= 996.0 + (Speed / 100)) {
					Bad(3);
					Linedelete(3);
				}
			}
		}
	}
	else if (Notes[3][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_M) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[3][0].y >= 916.0 - (Speed / 100) && Notes[3][0].y <= 956.0 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
			}
		}
	}
	else if (Notes[3][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_J) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[3][0].y >= 916.0 - (Speed / 100) && Notes[3][0].y <= 956.0 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
			}
		}
	}
	else if (Notes[3][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_U) == 1) { //F
			if (!Notes[0].empty()) {
				if (Notes[3][0].y >= 916.0 - (Speed / 100) && Notes[3][0].y <= 956.0 + (Speed / 100)) {
					Great(3,Notes[3][0].NotesColor);
					Linedelete(3);
				}
			}
		}
	}


	//通り過ぎた後の処理
	for (int i = 0, n = (signed)Notes.size(); i < n; i++) {
		if (!Notes[i].empty()) {								//ノーツがあるとき
			
			if (Notes[i][0].y > 1000 && Notes[i].size() > 1) {
				//Notes.clear();
				Linedelete(i);
				if (i < 4) {
					bad_count++;
					combo = 0;
					if (Notes[i][0].NotesColor >= 4) {
						gaugecount += 1;
					}
					else {
						gaugecount += 7;
					}
				}
				if (gaugecount > 0) {
					gaugecount = 0;
				}
				if (gaugecount < -500) {
					gaugecount = -500;
				}
			}
		}
	}

	combocount--;

	score[CSelectNum][DSelectNum] = (((great_count) + (ok_count / 2))) * 1000000 / notescount;

	//5レーン目のエフェクトなど
	if (Notes[4][0].y > 936) {
		switch (Notes[4][0].NotesColor) {
		case 0:
			break;
		case 1:
			if (begin_flag == true) {
				PlaySoundMem(Music[CSelectNum], DX_PLAYTYPE_BACK);
				begin_flag = false;
			}
			break;
		case 2:
			if (end_flag == false) {
				StopSoundMem(Music[1]);
				end_flag = true;
			}
			break;
		case 3:
			rightcount = 255;
			break;
		default:
			break;
		}

	}

	if (gaugecount <= -350) {
		clear_flag[CSelectNum][DSelectNum] = 1;  //クリアにする
	}
	else {
		clear_flag[CSelectNum][DSelectNum] = 0;
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //すべてを終える
		exit(1);
	}
}


//描画
void Game::Draw() {
	BaseScene::Draw();  //親クラスの描画メソッドを呼ぶ
	DrawString(465, 10, "ゲーム画面", GetColor(255, 255, 255));

	DrawRotaGraph(825, 540, 1.0, 0.0, Otherimg[0], TRUE);
	tennmetu++;
	if (tennmetu % 3 == 1) {
		DrawRotaGraph(825, 965, 1.0, 0.0, Otherimg[1], TRUE);
	}

	if (CheckHitKey(KEY_INPUT_V) != 0 || CheckHitKey(KEY_INPUT_F) != 0 || CheckHitKey(KEY_INPUT_R) != 0) {
		keyrightcount[0] = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyrightcount[0]);
		DrawRotaGraph3(674 + 76 * 0, 756, 0, 0, 1.0, 1.0, 0.0, Otherimg[3], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if (CheckHitKey(KEY_INPUT_B) != 0 || CheckHitKey(KEY_INPUT_G) != 0 || CheckHitKey(KEY_INPUT_T) != 0) {
		keyrightcount[1] = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyrightcount[1]);
		DrawRotaGraph3(674 + 76 * 1, 756, 0, 0, 1.0, 1.0, 0.0, Otherimg[3], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if (CheckHitKey(KEY_INPUT_N) != 0 || CheckHitKey(KEY_INPUT_H) != 0 || CheckHitKey(KEY_INPUT_Y) != 0) {
		keyrightcount[2] = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyrightcount[2]);
		DrawRotaGraph3(674 + 76 * 2, 756, 0, 0, 1.0, 1.0, 0.0, Otherimg[3], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	if (CheckHitKey(KEY_INPUT_M) != 0 || CheckHitKey(KEY_INPUT_J) != 0 || CheckHitKey(KEY_INPUT_U) != 0) {
		keyrightcount[3] = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyrightcount[3]);
		DrawRotaGraph3(674 + 76 * 3, 756, 0, 0, 1.0, 1.0, 0.0, Otherimg[3], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	

	DrawRotaGraph(1500, 600, 0.4, 0.0, Otherimg[9], TRUE);
	DrawRotaGraph(1500, 600, 0.3, 0.0, Jacketimg[CSelectNum], TRUE);

	DrawRotaGraph(825, 955, 1.0, 0.0, Otherimg[1], TRUE);
	DrawRotaGraph(825, 916, 1.0, 0.0, Otherimg[2], TRUE); //判定線はy936
	DrawRotaGraph(825, 956, 1.0, 0.0, Otherimg[2], TRUE);


	if (gaugecount <= -350) {
		DrawExtendGraph(1110, 340 + 500 + gaugecount, 1110 + 20, 840, Otherimg[5], TRUE);    //最長500
	}
	else {
		DrawExtendGraph(1110, 340 + 500 + gaugecount, 1110 + 20, 840, Otherimg[4], TRUE);    //最長500
	}
	
	DrawExtendGraph(1100, 100, 1100 + 40, 100 + 750, Otherimg[6], TRUE);
	DrawLine(1110, 490, 1130, 490, 0xff0000, true);


	DrawRotaGraph3(0, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[7], TRUE);
	DrawRotaGraph3(1120, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[7], TRUE);

	if (tennmetu % 2 == 1) {
		if (starttime > 0) {
			if (starttime < 150) {
				DrawString(775, 800, "READY...", GetColor(120, 120, 255));
			}
			if (starttime < 50) {
				DrawString(775, 850, "START", GetColor(120, 120, 255));
			}
		}

		if (endtime > 0 && end_flag == true) {
			if (endtime < 200) {
				if (clear_flag[CSelectNum][DSelectNum] == 1) {
					DrawString(775, 850, "CLEAR", GetColor(120, 120, 255));
				}
				else {
					DrawString(775, 850, "FAIL", GetColor(120, 120, 255));
				}
			}
		}	
	}

	

	// -Y_num * Speed * ((60.0 / BPM) / (Beat / 4))
	for (int j = 0, k = Notes.size() - 1; j < k; j++) {
		if(!Notes[j].empty()){
			for (int i = 0, n = (signed)Notes[j].size() - 1; i < n; i++) {
				if (Notes[j][i].y > 0) { //画面内にある時
					switch (Notes[j][i].NotesColor) {
					case 0:
						
						break;
					case 1:
						//DrawGraph(Notes[j][i].x, Notes[j][i].y, Notesimg[0], true);        リファレンスによって座標が違う
						//DrawRotaGraph(Notes[j][i].x, Notes[j][i].y, 1.0, 0.0, Notesimg[0], TRUE);
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0, 0.0, Notesimg[0], FALSE);
						break;
					case 2:
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0, 0.0, Notesimg[1], FALSE);
						break;
					case 3:
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0, 0.0, Notesimg[2], FALSE);
						break;
					case 4:
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0 * Speed * ((60.0 / BPM) / (Beat / 4)), 0.0, Notesimg[3], FALSE);
						break;
					case 5:
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0 * Speed * ((60.0 / BPM) / (Beat / 4)), 0.0, Notesimg[4], FALSE);
						break;
					case 6:
						DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0 * Speed * ((60.0 / BPM) / (Beat / 4)), 0.0, Notesimg[5], FALSE);
						break;
					default:

						break;
					}
				}
			}
		}
	}

	if (rightcount < 255) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, rightcount);
		DrawRotaGraph3(0, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[8], TRUE);
		DrawRotaGraph3(1120, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[8], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	
	if (tennmetu % 2 == 1) {
		for (int i = 0; i < 4; i++) {
			if (judge_great[i] > 0) {
				DrawString(670 + 76 * i, 750, "GREAT", GetColor(120, 120, 255));
			}
			if (judge_ok[i] > 0) {
				DrawString(690 + 76 * i, 750, "OK", GetColor(255, 120, 80));
			}
			if (judge_bad[i] > 0) {
				DrawString(680 + 76 * i, 750, "BAD", GetColor(255, 80, 120));
			}
		}
		if (combocount > 0) {
			DrawFormatString(810, 700, 0xff00ff, "%d", combo);
		}
	}

	SetFontSize(32);
	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}


}
