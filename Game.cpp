#include "Game.h"
#include "DxLib.h"
#include <stdio.h>

using namespace std;

//コンストラクタ--------------------------------------------------------------------------
Game::Game() : BaseScene() {

	Initialize();

	SelectTitle[0].SMake(1350, 800, 280, "ハイスピ2000", 1, 2, 4, 6);  //5つの構造体に中身を与える
	SelectTitle[1].SMake(1350, 800, 160, "Heaven helps you", 1, 3, 5, 7);
	SelectTitle[2].SMake(1350, 800, 250, "UN Equald", 3, 5, 7, 9);
	SelectTitle[3].SMake(1350, 800, 178, "Gear", 2, 4, 6, 8);
	SelectTitle[4].SMake(1350, 800, 165, "INVASION", 3, 5, 7, 10);
	SelectTitle[5].SMake(1350, 800, 0, "----------EXIT----------", 0, 0, 0, 0);

	string text_name;
	text_name = "譜面/test" + to_string(CSelectNum) + "," + to_string(DSelectNum) + ".txt";


	//ファイル読み込み
	ifstream n_file(text_name);
	if (n_file.fail()) {	// ファイル読み込み失敗
		DxLib_End();
	}
	else {
		string str;

		//タイトルなどの読み込み
		getline(n_file, str);
		f_title = str;
		getline(n_file, str);
		f_bpm = str;
		BPM = stoi(f_bpm);
		getline(n_file, str);
		f_beat = str;
		Beat = stoi(f_beat);
		getline(n_file, str);
		f_speed = str;
		Speed = stoi(f_speed);

		notescount = 0.0;
		int Y_num = 0;
		while (getline(n_file, str)) {
			for (int i = 0; i < LANE + 1; i++) {

				if (str[i] != '0') {
					Notes[i].push_back(NotesBase());	//0のとき、何もない空で間を埋める。(何も与えない)

					//テキストの数字によってノーツの初期座標と種類を与える
					switch (str[i]) {
					case '1':
						//Notes[i][(signed)Notes[i].size() - 1].Init(711 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 1);    リファレンスによって座標が違う
						//Notes[i][(signed)Notes[i].size() - 1].Init(674 + 76 * i, -Y_num * Speed * ((60.0 / BPM) / (Beat / 4)), 2);
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 1);
						break;
					case '2':
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 2);
						break;
					case '3':
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 3);
						break;
					case '4':
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 4);
						break;
					case '5':
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 5);
						break;
					case '6':
						Notes[i][(signed)Notes[i].size() - 1].Init(NotesX(i), NotesY(-Y_num), 6);
						break;
					default:
						break;
					}

					//5レーン目を除く譜面中のノーツ数をカウント
					if (i < LANE) {
						notescount++;
					}

				}
			}
			Y_num++;
		}
		for (int j = 0; j < Notes.size(); j++) { Notes[j].resize(Notes[j].size() + 1); }
	}
}

//デストラクタ--------------------------------------------------------------------------
Game::~Game() {
	Finalize();
}


//初期化--------------------------------------------------------------------------
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
	Notesimg[6] = LoadGraph("画像/Notes/ノーツef.png");

	Jacketimg[0] = LoadGraph("画像/ジャケット/selectA.png");
	Jacketimg[1] = LoadGraph("画像/ジャケット/hellnear.png");
	Jacketimg[2] = LoadGraph("画像/ジャケット/unequald_j.png");
	Jacketimg[3] = LoadGraph("画像/ジャケット/selectD.png");
	Jacketimg[4] = LoadGraph("画像/ジャケット/select2.png");
	Jacketimg[5] = 0;
	
	Music[0] = LoadSoundMem("音/曲/ﾕｳﾃﾗｳﾁ（声もﾕｳﾃﾗｳﾁ）.wav");
	Music[1] = LoadSoundMem("音/曲/ﾕｳﾃﾗｳﾁ（声もﾕｳﾃﾗｳﾁ）.wav");
	Music[2] = 0;
	Music[3] = 0;
	Music[4] = 0;
	Music[5] = 0;

	NowTime = 0.0;  //現在の時間
	OldTime = 0.0;  //一つ前の時間
	linedowner = 0.0;

	//待機時間
	starttime = 300;
	endtime = 300;

	//背景の照明時間
	rightcount = 255;


	for (int i = 0; i < LANE; i++) {
		keyrightcount[i] = 255;
		judge_great[i] = 0, judge_ok[i] = 0, judge_bad[i] = 0;
	}

	combo = 0,combocount = 0;
	
	gaugecount = 0.0;
}

//メモリ開放--------------------------------------------------------------------------
void Game::Finalize() {
	//画像削除
	DeleteGraph(mImageHandle);

	//ノーツ画像削除
	for (int i = 0; i < NOTESIMG; i++) {
		DeleteGraph(Notesimg[i]);
	}

	//画面パーツ削除
	for (int i = 0; i < Other; i++) {
		DeleteGraph(Otherimg[i]);
	}

	//ジャケット削除
	for (int i = 0; i < SelectNum; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	//音楽削除
	for (int i = 0; i < SelectNum; i++) {
		DeleteSoundMem(Music[i]);
	}

	//ノーツ削除
	Notes[0].clear();
	Notes[0].shrink_to_fit();
}


//更新--------------------------------------------------------------------------

void Game::Update() {
	if (counter < Illum && fade_flag == false) {  //最初のフェードイン
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //切り替わりのフェードアウト
		counter = counter - 5;
	}


	//画面移行
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		StopSoundMem(Music[1]);
		fade_flag = true;
	}

	//フェードアウトで真っ暗のときにシーンを替える
	if (counter == 0 && fade_flag == true) {

		GaugeCharge();

		BaseScene::NowScene = eScene::eScene_Result;
	}

	//背景の照明時間
	if (rightcount > 0) { 
		rightcount = rightcount - 15;
	}

	//キーライトの表示時間
	for (int i = 0; i < LANE; i++) {
		if (keyrightcount[i] > 0) {
			keyrightcount[i] = keyrightcount[i] - 15;
		}
		judge_great[i]--;
		judge_ok[i]--;
		judge_bad[i]--;
	}

	//時間を取得
	if (start_flag == true) {
		StartTime = GetNowHiPerformanceCount();
		OldTime = StartTime;

		start_flag = false;
	}
	else {
		OldTime = NowTime;
	}

	//時間を取得
	NowTime = GetNowHiPerformanceCount();
	difference = (double)(NowTime - OldTime);

	//落下処理
	if (starttime == 0) {
		for (int i = 0, n = (signed)Notes.size(); i < n; i++) {
			if (!Notes[i].empty() == false) { continue; }      
			
			//ノーツがあるとき
			for (int j = 0, m = Notes[i].size(); j < m; j++) {
				Notes[i][j].Down(difference, Speed);
			}
		}
	}

	//譜面が落下するまでの待機時間を進める
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
		if (Keyboard::GetKey(KEY_INPUT_V) == 1) Judgement(0);
	}
	if (Notes[0][0].NotesColor == 2){
		if (Keyboard::GetKey(KEY_INPUT_F) == 1) Judgement(0);
	}
	if (Notes[0][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_R) == 1) Judgement(0);
	}
	if (Notes[0][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_V) == 1) LongJudgement(0);
	}
	if (Notes[0][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_F) == 1) LongJudgement(0);
	}
	if (Notes[0][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_R) == 1) LongJudgement(0);
	}


	if (Notes[1][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_B) == 1) Judgement(1);
	}
	if (Notes[1][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_G) == 1) Judgement(1);
	}
	if (Notes[1][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_T) == 1) Judgement(1);
	}
	if (Notes[1][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_B) == 1) LongJudgement(1);
	}
	if (Notes[1][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_G) == 1) LongJudgement(1);
	}
	if (Notes[1][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_T) == 1) LongJudgement(1);
	}

	if (Notes[2][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_N) == 1) Judgement(2);
	}
	if (Notes[2][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_H) == 1) Judgement(2);
	}
	if (Notes[2][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_Y) == 1) Judgement(2);
	}
	if (Notes[2][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_N) == 1) LongJudgement(2);
	}
	if (Notes[2][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_H) == 1) LongJudgement(2);
	}
	if (Notes[2][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_Y) == 1) LongJudgement(2);
	}

	if (Notes[3][0].NotesColor == 1) {
		if (Keyboard::GetKey(KEY_INPUT_M) == 1) Judgement(3);
	}
	if (Notes[3][0].NotesColor == 2) {
		if (Keyboard::GetKey(KEY_INPUT_J) == 1) Judgement(3);
	}
	if (Notes[3][0].NotesColor == 3) {
		if (Keyboard::GetKey(KEY_INPUT_U) == 1) Judgement(3);
	}
	if (Notes[3][0].NotesColor == 4) {
		if (CheckHitKey(KEY_INPUT_M) == 1) LongJudgement(3);
	}
	if (Notes[3][0].NotesColor == 5) {
		if (CheckHitKey(KEY_INPUT_J) == 1) LongJudgement(3);
	}
	if (Notes[3][0].NotesColor == 6) {
		if (CheckHitKey(KEY_INPUT_U) == 1) LongJudgement(3);
	}


	//通り過ぎた後の処理
	for (int i = 0, n = (signed)Notes.size(); i < n; i++) {
		if (!Notes[i].empty() == false) { continue; }    //ノーツがあるとき

		if (Notes[i][0].y > 1000 && Notes[i].size() > 1) {

			Linedelete(i);  //ノーツを削除

			if (i < LANE == false) { continue; }
			bad_count++;
			combo = 0;
			if (Notes[i][0].NotesColor >= 4) {
				gaugecount += 1;
			}
			else {
				gaugecount += 7;
			}
		}

		//ゲージはみ出し防止
		if (gaugecount > 0) {
			gaugecount = 0;
		}
		if (gaugecount < -500) {
			gaugecount = -500;
		}
	}
		
	
	combocount--;

	//スコアを判定の数から算出(満点は1000000)
	score[CSelectNum][DSelectNum] = ((great_count) + (ok_count / 2)) * 1000000 / notescount;

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
				StopSoundMem(Music[CSelectNum]);
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


//描画--------------------------------------------------------------------------
void Game::Draw() {
	BaseScene::Draw();  //親クラスの描画メソッドを呼ぶ
	//DrawString(465, 10, "ゲーム画面", GetColor(255, 255, 255));

	DrawRotaGraph(825, 540, 1.0, 0.0, Otherimg[0], TRUE);

	tennmetu++;
	if (tennmetu % 3 == 1) {
		DrawRotaGraph(825, 965, 1.0, 0.0, Otherimg[1], TRUE);
	}

	//キーのライトをレーンごとに表示
	if (CheckHitKey(KEY_INPUT_V) != 0 || CheckHitKey(KEY_INPUT_F) != 0 || CheckHitKey(KEY_INPUT_R) != 0) KeyRight(0);
	if (CheckHitKey(KEY_INPUT_B) != 0 || CheckHitKey(KEY_INPUT_G) != 0 || CheckHitKey(KEY_INPUT_T) != 0) KeyRight(1);
	if (CheckHitKey(KEY_INPUT_N) != 0 || CheckHitKey(KEY_INPUT_H) != 0 || CheckHitKey(KEY_INPUT_Y) != 0) KeyRight(2);
	if (CheckHitKey(KEY_INPUT_M) != 0 || CheckHitKey(KEY_INPUT_J) != 0 || CheckHitKey(KEY_INPUT_U) != 0) KeyRight(3);
	

	DrawRotaGraph(1500, 600, 0.4, 0.0, Otherimg[9], TRUE);
	DrawRotaGraph3(1600, 850, 0, 0, 0.1, 0.05, 0.0, Otherimg[9], TRUE);
	DrawRotaGraph3(0, 350, 0, 0, 0.5, 0.05, 0.0, Otherimg[9], TRUE);

	//ジャケット、タイトル、BPM、現在のスコアを表示
	DrawRotaGraph(1500, 600, 0.3, 0.0, Jacketimg[CSelectNum], TRUE);
	SelectTitle[CSelectNum].Draw();
	DrawString(1625, 840, "BPM", GetColor(255, 120, 255));
	DrawFormatString(1640, 870, 0xffffff, "%d", SelectTitle[CSelectNum].bpm);
	DrawString(50, 345, "SCORE", GetColor(50, 50, 200));
	DrawFormatString(440, 370, 0xff00ff, "%d", score[CSelectNum][DSelectNum]);
	

	DrawRotaGraph(825, 955, 1.0, 0.0, Otherimg[1], TRUE);
	DrawRotaGraph(825, 916, 1.0, 0.0, Otherimg[2], TRUE); //判定線はy936
	DrawRotaGraph(825, 956, 1.0, 0.0, Otherimg[2], TRUE);

	//クリア判定の色彩変更
	if (gaugecount <= -350) {
		DrawExtendGraph(1110, 340 + 500 + gaugecount, 1110 + 20, 840, Otherimg[5], TRUE);    //最長500
	}
	else {
		DrawExtendGraph(1110, 340 + 500 + gaugecount, 1110 + 20, 840, Otherimg[4], TRUE);    //最長500
	}
	
	//ゲージケース
	DrawExtendGraph(1100, 100, 1100 + 40, 100 + 750, Otherimg[6], TRUE);
	DrawLine(1110, 490, 1130, 490, 0xff0000, true);


	DrawRotaGraph3(0, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[7], TRUE);
	DrawRotaGraph3(1120, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[7], TRUE);

	if (tennmetu % 2 == 1) {

		//待機コメントを表示
		if (starttime > 0) {
			if (starttime < 150) {
				DrawString(775, 800, "READY...", GetColor(120, 120, 255));
			}
			if (starttime < 50) {
				DrawString(775, 850, "START", GetColor(120, 120, 255));
			}
		}

		//曲終了時にクリアか否か表示
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

	//線
	if (starttime == 0) {
		linedowner += Speed * (difference * 0.000001);
		for (int i = 0; i < BPM * 4; i++) {
			if (i % 4 == 0) {
				DrawLine(0 + 650, -i * (Speed * (60.0 / BPM)) * 4 + linedowner, 1920 - 900, -i * (Speed * (60.0 / BPM)) * 4 + linedowner, 0x505050, true);

			}
		}
	}

	//ノーツの情報を基に種類ごとに表示
	for (int j = 0, k = Notes.size() - 1; j < k; j++) {
		if (!Notes[j].empty() == false) {continue;}
		for (int i = 0, n = (signed)Notes[j].size() - 1; i < n; i++) {
			if (Notes[j][i].y > 0) { //画面内にある時
				switch (Notes[j][i].NotesColor) {
				case 0:

					break;
				case 1:
					DrawNotes(j, i, 0);
					break;
				case 2:
					DrawNotes(j, i, 1);
					break;
				case 3:
					DrawNotes(j, i, 2);
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

	//背景の照明
	if (rightcount < 255) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, rightcount);
		DrawRotaGraph3(0, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[8], TRUE);
		DrawRotaGraph3(1120, -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[8], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	
	//判定を表示
	if (tennmetu % 2 == 1) {    //点滅
		for (int i = 0; i < LANE; i++) {
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

	
	Fadeout();
}
