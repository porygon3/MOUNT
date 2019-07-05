#pragma once

#include "Master.h"
#include "ISceneChanger.h"
#include "Keyboard.h"

#define SelectNum 6 //�W���P�b�g�������l
#define Difficult 4
#define LEVEL 4

#define Other 10
#define SENum 3
#define FPattern 3

#define Illum 255

extern int timer;

// �t�F�[�h�J�E���^
extern int counter;
//�t�F�[�h�t���O
extern bool fade_flag;

// �t���b�V���J�E���^
extern int counter2;
//�t���b�V���t���O
extern bool flash_flag;

//�I�Ȉړ��p�t���O
extern bool up_flag;
extern bool down_flag;

//��Փx�ړ��p�t���O
extern bool difup_flag;
extern bool difdown_flag;


//�v���ŕ\������ȏ��̍\����
typedef struct {
	int x, y; // ���W
	char name[256]; // ����

	int bpm;
	int level[LEVEL];
	int point[LEVEL];

	//�Ȃ̏����쐬
	void SMake(int _x, int _y,int _bpm, char _name[256], int a, int b, int c, int d){
		x = _x;
		y = _y;
		bpm = _bpm;
		for (int i = 0; i < 256; i++){
			name[i] = _name[i];
		}

		level[0] = a;
		level[1] = b;
		level[2] = c;
		level[3] = d;

		//���ւɕK�v�ȃG�l���M�[(��Փx��10�{)
		for (int i = 0; i < LEVEL; i++) {
			point[i] = level[i] * 10;
		}


	}

	void DMake(int _x, int _y, char _name[256]) {
		x = _x;
		y = _y;
		for (int i = 0; i < 256; i++) {
			name[i] = _name[i];
		}
		
	}

	void Add() {
		x -= 1;
		y += 10;
		if (y >= 1350) {
			x = 1325;
			y = -150;
		}
	}
	void Sub() {
		x += 1;
		y -= 10;
		if (y <= -400) {
			x = 1200;
			y = 1100;
		}
	}
	void Draw() { //�Ă΂ꂽ��`��
		DrawFormatString(x, y, 0xffffff, "%s", name);
	}

}BaseMenu;

class BaseScene : public Master {  //Master�̃����o���p��

protected:
	int mImageHandle;
	int mSoundHandle;
	int Jacketimg[SelectNum];
	int Otherimg[Other];
	int Music[SelectNum];
	int SE[SENum];
	int tennmetu;
	int fsHandle[FPattern];


	static int CSelectNum;
	static int DSelectNum;
	static int great_count, ok_count, bad_count;
	static int highscore[SelectNum][Difficult],score[SelectNum][Difficult];
	static int clear_flag[SelectNum][Difficult];
	static int unlock_flag[SelectNum][Difficult];
	static int GaugeEnergie;
	static eScene NowScene;

	//�t�F�[�h�A�E�g�p�֐�
	void Fadeout() {
		if (counter < Illum){
			//�t�F�[�h�A�E�g�p�̍��������`
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Illum - counter);
			DrawBox(0, 0, 1920, 1080, 0x000000, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Illum);
		}
	}

	void Flash() {
		if (counter2 < Illum) {
			//�t���b�V���p�̍��������`
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Illum - counter2);
			DrawBox(0, 0, 1920, 1080, 0xffffff, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Illum);
		}
	}


public:
	BaseScene();
	virtual  ~BaseScene() {};
	virtual void Initialize() override {};
	virtual void Finalize() override;
	virtual void Update() override {};
	virtual void Draw() override;

	eScene GetNowScene();

};
