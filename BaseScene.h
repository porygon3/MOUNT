#pragma once

#include "Master.h"
#include "ISceneChanger.h"
#include "Keyboard.h"

extern int counter; // �t�F�[�h�J�E���^
extern bool fade_flag; // �t�F�[�h�A�E�g����̂��t�F�[�h�C������̂��̔���
extern bool up_flag;
extern bool down_flag;

extern bool difup_flag;
extern bool difdown_flag;


typedef struct {   //�\���̂�錾
	int x, y; // ���W
	char name[256]; // ����

	int bpm;
	int level[4];

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
	int Jacketimg[6];
	int Otherimg[10];
	int Music[6];
	int SE[3];
	int tennmetu;
	static int CSelectNum; //static�����o�ϐ�
	static int DSelectNum;
	static int great_count, ok_count, bad_count;
	static int highscore[6][4],score[6][4];
	static int clear_flag[6][4];
	static int unlock_flag[6][4];
	static eScene NowScene;
public:
	BaseScene();
	virtual  ~BaseScene() {};
	virtual void Initialize() override {};
	virtual void Finalize() override;
	virtual void Update() override {};
	virtual void Draw() override;

	eScene GetNowScene();

};
