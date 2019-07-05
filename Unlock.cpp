#include "Unlock.h"
#include "DxLib.h"

//�R���X�g���N�^--------------------------------------------------------------------------
Unlock::Unlock() :BaseScene() {

	Initialize();

	mImageHandle = 0;
	
	unlock_flag[CSelectNum][DSelectNum] = 1;
	//GaugeEnergie -= SelectTitle[CSelectNum].point[DSelectNum];

	SelectTitle[0].SMake(700, 900, 280, "�n�C�X�s2000", 1, 2, 4, 6);  //5�̍\���̂ɒ��g��^����
	SelectTitle[1].SMake(700, 900, 160, "Heaven helps you", 1, 3, 5, 7);
	SelectTitle[2].SMake(700, 900, 250, "UN Equald", 3, 5, 7, 9);
	SelectTitle[3].SMake(700, 900, 178, "Gear", 2, 4, 6, 8);
	SelectTitle[4].SMake(700, 900, 165, "INVASION", 3, 5, 7, 10);
	SelectTitle[5].SMake(700, 900, 0, "----------EXIT----------", 0, 0, 0, 0);

	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);

}

//�f�X�g���N�^--------------------------------------------------------------------------
Unlock::~Unlock() {

	Finalize();

}

//������--------------------------------------------------------------------------
void Unlock::Initialize() {
	
	timer = 140;
	mImageHandle = LoadGraph("�摜/���/select.png");
	mSoundHandle = LoadSoundMem("��/����.wav");

	Jacketimg[0] = LoadGraph("�摜/�W���P�b�g/RH.png");
	Jacketimg[1] = LoadGraph("�摜/�W���P�b�g/hellnear.png");
	Jacketimg[2] = LoadGraph("�摜/�W���P�b�g/unequald_j.png");
	Jacketimg[3] = LoadGraph("�摜/�W���P�b�g/darkRL.png");
	Jacketimg[4] = LoadGraph("�摜/�W���P�b�g/invasion.png");
	Jacketimg[5] = 0;

	Otherimg[0] = LoadGraph("�摜/���/select2.png");
	Otherimg[1] = LoadGraph("�摜/���/big_illum.png");
	Otherimg[2] = 0;
	Otherimg[3] = 0;
	Otherimg[4] = 0;
	Otherimg[5] = 0;
	Otherimg[6] = 0;
	Otherimg[7] = 0;
	Otherimg[8] = 0;
	Otherimg[9] = 0;

	fsHandle[0] = CreateFontToHandle(0, 128, -1, DX_FONTTYPE_ANTIALIASING);
	fsHandle[1] = 0;
	fsHandle[2] = 0;

}

//�������J��--------------------------------------------------------------------------
void Unlock::Finalize() {
	DeleteGraph(mImageHandle);
	for (int i = 0; i < SelectNum; i++) {
		DeleteGraph(Jacketimg[i]);
	}

	for (int i = 0; i < Other; i++) {
		DeleteGraph(Otherimg[i]);
	}

	for (int i = 0; i < FPattern; i++) {
		DeleteGraph(fsHandle[i]);
	}
	DeleteSoundMem(mSoundHandle);
}

//�X�V--------------------------------------------------------------------------
void Unlock::Update() {

	tennmetu++;

	if (counter2 < Illum && flash_flag == false) {  //�ŏ��̃t�F�[�h�C��
		counter2 = counter2 + 15;
	}
	else if (counter2 > 0 && flash_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g
		counter2 = counter2 - 15;
	}


	if (counter2 > Illum - 1) {
		if (timer > 0) {
			timer--;
		}
		else {
			flash_flag = true;
		}
	}


	if (counter2 == 0 && flash_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		BaseScene::NowScene = eScene::eScene_Select;
	}


	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}
}

//�`��--------------------------------------------------------------------------
void Unlock::Draw() {
	BaseScene::Draw();
	DrawRotaGraph(960, 500, 0.6, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();
	SelectDif[DSelectNum].Draw();

	DrawRotaGraph3(1600 - (timer * 24), 200, 0, 0, 1.0, 1.0, 0.0, Otherimg[1], TRUE);
	DrawRotaGraph3(-1000 + (timer * 24), -200, 0, 0, 1.0, 1.0, 0.0, Otherimg[1], TRUE);

	DrawString(1300, 900, "BPM", GetColor(255, 120, 255));
	DrawFormatString(1375, 900, 0xffffff, "%d", SelectTitle[CSelectNum].bpm);


	if (tennmetu % 2 == 1) {    //�_��
		DrawStringToHandle(960, 700, "UNLOCK", GetColor(0 + counter2 / 2, 0 + counter2 / 2, 255), fsHandle[0]);
	}

	//DrawFormatString(0, 0, 0xffffff, "%d", GaugeEnergie);
	Flash();
}