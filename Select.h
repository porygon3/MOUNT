#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define UNLOCK 3
#define SStart 1300
#define Dbox 350

class Select : public BaseScene {
private:
	int x = 0;
	int y = 0;

	int upcount;
	int downcount;
	int difupcount;
	int difdowncount;

	bool music_flag;
	bool u_flag[SelectNum];

	BaseMenu SelectTitle[SelectNum]; //  基底で作った構造体を6つ宣言

	BaseMenu SelectDif[Difficult]; //難易度4つを宣言

	double BPM, Beat, Speed;
	string f_title, f_bpm, f_beat, f_speed, f_notes;

	void UnlockDraw() {

		for (int i = 0; i < UNLOCK; i++) {

			DrawString(550, 400, "[LOCK]", GetColor(255, 255, 255));
			if (clear_flag[CSelectNum][i] == 1) {

				u_flag[CSelectNum] = 1;

				if (SelectTitle[CSelectNum].point[DSelectNum] <= GaugeEnergie) {

					DrawString(500, 500, "解禁が可能です", GetColor(255, 255, 255));

				}
				else {
					DrawString(350, 500, "ゲージエネルギーが不足しています", GetColor(255, 255, 255));
				}

				DrawString(350, 700, "必要なGE:", GetColor(255, 255, 255));
				DrawFormatString(550, 700, GetColor(255, 120, 120), "%d", SelectTitle[CSelectNum].point[DSelectNum]);

			}

			if (u_flag[CSelectNum] == 0) {
				DrawString(350, 500, "いずれかの難易度をクリアすると", GetColor(255, 255, 255));
				DrawString(350, 550, "解禁が可能になります", GetColor(255, 255, 255));
			}
		}
	}
	
public:
	Select();
	

	int DifCount;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	
	~Select();

};
