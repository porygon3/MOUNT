#include "Result.h"
#include "Game.h"
#include "DxLib.h"

//�R���X�g���N�^--------------------------------------------------------------------------
Result::Result() : BaseScene() {
	Initialize();

	SelectTitle[0].SMake(300, 10, 280, "�n�C�X�s2000", 1, 2, 4, 6);  //5�̍\���̂ɒ��g��^����
	SelectTitle[1].SMake(300, 10, 160, "Heaven helps you", 1, 3, 5, 7);
	SelectTitle[2].SMake(300, 10, 250, "UN Equald", 3, 5, 7, 9);
	SelectTitle[3].SMake(300, 10, 178, "Gear", 2, 4, 6, 8);
	SelectTitle[4].SMake(300, 10, 165, "INVASION", 3, 5, 7, 10);
	SelectTitle[5].SMake(300, 10, 0, "----------EXIT----------", 0, 0, 0, 0);

}

//�f�X�g���N�^--------------------------------------------------------------------------
Result::~Result() {
	Finalize();
}

//������--------------------------------------------------------------------------
void Result::Initialize() {
	if (clear_flag[CSelectNum][DSelectNum] == 1) {
		mImageHandle = LoadGraph("�摜/���/�N���A.png");
	}
	else {
		mImageHandle = LoadGraph("�摜/���/��N���A.png");
	}
	
	SE[0] = LoadSoundMem("��/�ړ�.wav");
	SE[1] = LoadSoundMem("��/����.wav");

	Jacketimg[0] = LoadGraph("�摜/�W���P�b�g/selectA.png");
	Jacketimg[1] = LoadGraph("�摜/�W���P�b�g/hellnear.png");
	Jacketimg[2] = LoadGraph("�摜/�W���P�b�g/unequald_j.png");
	Jacketimg[3] = LoadGraph("�摜/�W���P�b�g/selectD.png");
	Jacketimg[4] = LoadGraph("�摜/�W���P�b�g/select2.png");
	Jacketimg[5] = 0;

	Otherimg[0] = LoadGraph("�摜/���/select2.png");
	Otherimg[1] = LoadGraph("�摜/���/select2yellow.png");
	Otherimg[2] = LoadGraph("�摜/���/select2red.png");
	Otherimg[3] = LoadGraph("�摜/���/select2black.png");
	Otherimg[4] = LoadGraph("�摜/���/part.png");
	Otherimg[5] = LoadGraph("�摜/���/part2.png");
	Otherimg[6] = 0;
	Otherimg[7] = 0;
	Otherimg[8] = 0;
	Otherimg[9] = 0;

	drawcount = 100;
	soundcount = 100;
	flag = 1;
	Rscore = score[CSelectNum][DSelectNum];

	fsHandle[0] = CreateFontToHandle(0, 32, -1, DX_FONTTYPE_ANTIALIASING);
	fsHandle[1] = CreateFontToHandle(0, 64, -1, DX_FONTTYPE_ANTIALIASING);
	fsHandle[2] = CreateFontToHandle(0, 256, -1, DX_FONTTYPE_ANTIALIASING);
}

//�������J��--------------------------------------------------------------------------
void Result::Finalize() {
	DeleteGraph(mImageHandle);
	for (int i = 0; i < SelectNum; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	for (int i = 0; i < Other; i++) {
		DeleteGraph(Otherimg[i]);
	}
	for (int i = 0; i < SENum; i++) {
		DeleteSoundMem(SE[i]);
	}
	for (int i = 0; i < FPattern; i++) {
		DeleteFontToHandle(fsHandle[i]);
	}

}

//�X�V--------------------------------------------------------------------------
void Result::Update() {
	if (counter < Illum && fade_flag == false) {  //�ŏ��̃t�F�[�h�C��
												//	SetDrawBright(counter, counter, counter);�ł�����
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g

		counter = counter - 5;
	}

	//��ʈڍs
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		StopSoundMem(Music[1]);
		fade_flag = true;	
	}
	
	//�t�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
	if (counter == 0 && fade_flag == true) {
		BaseScene::NowScene = eScene::eScene_Select;
	}


	if (drawcount > 0) {
		drawcount--;
	}
	if (soundcount > 0) {
		if (soundcount % 2 == 0) {
			PlaySoundMem(SE[0], DX_PLAYTYPE_BACK);
		}
		soundcount--;
	}
	else {
		if (flag == 1) {
			PlaySoundMem(SE[1], DX_PLAYTYPE_BACK);
			flag = 0;
		}
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}

}

//�`��--------------------------------------------------------------------------
void Result::Draw() {
	BaseScene::Draw();

	DrawRotaGraph(500, 500, 0.6, 0.0, Otherimg[DSelectNum], TRUE);
	DrawRotaGraph(500, 500, 0.4, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();

	//�ォ�珇�ԂɃp�[�c��\��
		if (drawcount < 100) DrawRotaGraph3(1000, 200, 0, 0, 1.0, 0.1, 0.0, Otherimg[0], TRUE);
		if (drawcount < 90)  DrawRotaGraph3(900, 450, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
		if (drawcount < 80)  DrawRotaGraph3(900, 600, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
		if (drawcount < 70)  DrawRotaGraph3(900, 750, 0, 0, 1.0, 0.05, 0.0, Otherimg[0], TRUE);
		if (drawcount < 50)  DrawRotaGraph3(-300, 400, 0, 0, 1.0, 1.0, 0.0, Otherimg[5], TRUE);
		if (drawcount == 0) {
			DrawRotaGraph3(1300, 750, 0, 0, 0.3, 0.3, 0.0, Otherimg[0], TRUE);

			//�����N����
			ScoreRank();

			//�N���A����N���A���\��
			if (clear_flag[CSelectNum][DSelectNum] == 1) {
				DrawStringToHandle(300, 850, "CLEAR", GetColor(130, 130, 255), fsHandle[2]);
			}
			else {
				DrawStringToHandle(300, 850, "FAIL", GetColor(255, 130, 130), fsHandle[2]);
			}
		}
						
	
	
	//���萔��\��
	if (drawcount < 90) {
		DrawStringToHandle(1000, 470, "GREAT", GetColor(120, 120, 255), fsHandle[0]);
		DrawFormatStringToHandle(1200, 470, GetColor(255, 255, 255), fsHandle[0],"%d" ,great_count);
	}
	if (drawcount < 80) {
		DrawStringToHandle(1000, 620, "OK", GetColor(255, 120, 80), fsHandle[0]);
		DrawFormatStringToHandle(1200, 620, GetColor(255, 255, 255), fsHandle[0], "%d", ok_count);
	}
	if (drawcount < 70) {
		DrawStringToHandle(1000, 770, "BAD", GetColor(255, 180, 120), fsHandle[0]);
		DrawFormatStringToHandle(1200, 770, GetColor(255, 255, 255), fsHandle[0], "%d", bad_count);
		DrawStringToHandle(1450, 900, "RANK", GetColor(130, 130, 255), fsHandle[0]);
		
	}
	if (drawcount < 70) {
		DrawStringToHandle(1000, 220, "SCERE", GetColor(255, 80, 120), fsHandle[1]);
		DrawFormatStringToHandle(1400, 250, GetColor(255, 255, 255), fsHandle[1], "%d", Rscore);
	}

	SelectDif[DSelectNum].Draw();
	
	//�V�L�^�̏㏑��
	if (highscore[CSelectNum][DSelectNum] < Rscore) {
		highscore[CSelectNum][DSelectNum] = Rscore;
	}

	Fadeout();
}