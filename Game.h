#pragma once

#include "BaseScene.h"
#include <deque>
#include <array>
#include <fstream>
#include <iostream>
#include <string>

#define LANE 4
#define ComDeci 10  //�����R���{��\�����鎞��
#define NOTESIMG 7

using namespace std;

//�Q�[����ʃN���X
class Game : public BaseScene {
private:

	
	int Notesimg[NOTESIMG];
	bool start_flag = true;
	bool notes_flag = true;
	bool begin_flag = true;
	bool end_flag = false;
	bool keylight_flag = false;
	double notescount;
	int rightcount;
	int keyrightcount[LANE];

	int judge_great[LANE],judge_ok[LANE],judge_bad[LANE];
	int combo,combocount;
	
	double gaugecount;  //�Q�[�W�̗e��
	

	LONGLONG StartTime; //��ʂɈڍs��������
	LONGLONG NowTime;   //���݂̎���
	LONGLONG OldTime;   //���̑O�̎���

	int starttime;
	int endtime;

	double linedowner;  //�Ȃ̔��q�ɍ��킹�č~��Ă����

	double difference;  //���݂̎��ԂƂ��̑O�̎��Ԃ̍�

	double BPM, Beat, Speed;
	string f_title,f_bpm, f_beat, f_speed, f_notes;

	//�m�[�c�̃X�e�[�^�X
	typedef struct {
		int x;
		double y;

		int NotesColor;

		//����
		void Down(double difference,double Speed) {
			y += Speed * (difference * 0.000001);
		}

		//�X�̃m�[�c�̃X�e�[�^�X��^����
		void Init(int _x, double _y, int _NotesColor) {
			x			= _x;
			y			= _y;
			NotesColor	= _NotesColor;
		}
		
	}NotesBase;

	//���ʂ̍\��
	array<deque<NotesBase>,LANE + 1>Notes = {};      //deque�̔z��


	int NotesX(int i) {
		int x = 0;
		x = 674 + 76 * i;
		return x;
	}

	int NotesY(int num) {
		int y = 0;
		y = num * Speed * ((60.0 / BPM) / (Beat / 4));
		return y;
	}


	//�m�[�c�폜
	void Linedelete(int num) {
		Notes[num].erase(Notes[num].begin());
	}

	//GREAT����
	void Great(int rean,int color) {
		great_count++;
		combo++;
		combocount = ComDeci;
		judge_great[rean] = ComDeci;
		if (gaugecount <= 0 && gaugecount >= -500) {
			if (color < 4) {
				gaugecount -= 1500 / notescount;
			}
			else {
				gaugecount -= 1500 / notescount / 8;
			}
			
		}
	}
	//OK����
	void Ok(int rean) {
		ok_count++;
		combo++;
		combocount = ComDeci;
		judge_ok[rean] = ComDeci;
		if (gaugecount <= 0 && gaugecount >= -500) {

			gaugecount -= 1500 / notescount / 2;
		}
	}
	//BAD����
	void Bad(int rean) {
		bad_count++;
		combo = 0;
		judge_bad[rean] = ComDeci;
		if (gaugecount <= 0 && gaugecount >= -500) {
			gaugecount += 5;
		}
	}

	//�L�[���C�g����
	void KeyRight(int rean) {
		keyrightcount[rean] = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyrightcount[rean]);
		DrawRotaGraph3(674 + 76 * rean, 756, 0, 0, 1.0, 1.0, 0.0, Otherimg[3], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}


	//3��ނ̃m�[�c����
	void Judgement(int rean) {

		if (!Notes[rean].empty()) {
			if (Notes[rean][0].y >= 916.0 - (Speed / 100) && Notes[rean][0].y <= 956.0 + (Speed / 100)) {
				Great(rean, Notes[rean][0].NotesColor);
				Linedelete(rean);
			}
			else if (Notes[rean][0].y >= 896.0 - (Speed / 100) && Notes[rean][0].y <= 976.0 + (Speed / 100)) {
				Ok(rean);
				Linedelete(rean);
			}
			else if (Notes[rean][0].y >= 876.0 - (Speed / 100) && Notes[rean][0].y <= 996.0 + (Speed / 100)) {
				Bad(rean);
				Linedelete(rean);
			}
		}
	}

	//3��ނ̃����O�m�[�c����
	void LongJudgement(int rean) {

		if (!Notes[rean].empty()) {
			if (Notes[rean][0].y >= 916.0 - (Speed / 100) && Notes[rean][0].y <= 956.0 + (Speed / 100)) {
				Great(rean, Notes[rean][0].NotesColor);
				Linedelete(rean);
			}
		}
	}

	//3��ނ̃m�[�c�\��
	void DrawNotes(int j,int i,int num) {
		DrawRotaGraph3(Notes[j][i].x, Notes[j][i].y - 7, 0, 0, 1.0, 1.0, 0.0, Notesimg[num], FALSE);
	}

	//�Q�[�W�G�l���M�[�����Z
	void GaugeCharge() {
		GaugeEnergie += ((int)(-gaugecount) / 10) * SelectTitle[CSelectNum].level[DSelectNum];
	}


public:
	BaseMenu SelectTitle[SelectNum];
	BaseMenu SelectDif[Difficult];
	Game::Game();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Game();

};