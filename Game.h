#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include <deque>
#include <array>
#include <fstream>
#include <iostream>
#include <string>


//ゲーム画面クラス
class Game : public BaseScene {
private:

	
	int Notesimg[7];
	bool start_flag = true;
	bool notes_flag = true;
	bool begin_flag = true;
	bool end_flag = false;
	bool keylight_flag = false;
	int notescount;
	int rightcount;
	int keyrightcount[4];

	int judge_great[4],judge_ok[4],judge_bad[4];
	int combo,combocount;
	
	double gaugecount;
	

	LONGLONG StartTime;
	LONGLONG NowTime;
	LONGLONG OldTime;

	int starttime;
	int endtime;

	double difference;
	double BPM,Beat,Speed;


	typedef struct {
		int x;
		double y;

		int NotesColor;

		//落下
		void Down(double difference,double Speed) {
			y += Speed * (difference * 0.000001);
		}
		void Init(int _x, double _y, int _NotesColor) {
			x			= _x;
			y			= _y;
			NotesColor	= _NotesColor;
		}
		
	}NotesBase;

	std::array<std::deque<NotesBase>,5>Notes = {};      //dequeの配列

	std::string f_title, f_bpm, f_beat, f_speed,f_notes;

	void Linedelete(int num) {
		Notes[num].erase(Notes[num].begin());
	}

	void Great(int rean,int color) {
		great_count++;
		combo++;
		combocount = 10;
		judge_great[rean] = 10;
		if (gaugecount <= 0 && gaugecount >= -500) {
			if (color < 4) {
				gaugecount -= 1500 / notescount;
			}
			else {
				gaugecount -= 1500 / notescount / 4;
			}
			
		}
	}
	void Ok(int rean) {
		ok_count++;
		combo++;
		combocount = 10;
		judge_ok[rean] = 10;
		if (gaugecount <= 0 && gaugecount >= -500) {

			gaugecount -= 1500 / notescount / 2;
		}
	}
	void Bad(int rean) {
		bad_count++;
		combo = 0;
		judge_bad[rean] = 10;
		if (gaugecount <= 0 && gaugecount >= -500) {
			gaugecount += 5;
		}
	}

	

public:
	Game::Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Game();

};