#include "Jacket.h"
#include "DxLib.h"

Jacket::Jacket() :BaseScene() {
	
}
Jacket::~Jacket() {

}

//������
void Jacket::Initialize() {
	mImageHandle = LoadGraph("�摜/���/game.png");
	mSoundHandle = LoadSoundMem("��/�Ȍ���.wav");

	Jacketimg[0] = LoadGraph("�摜/�W���P�b�g/selectA.png");
	Jacketimg[1] = LoadGraph("�摜/�W���P�b�g/hellnear.png");
	Jacketimg[2] = LoadGraph("�摜/�W���P�b�g/unequald_j.png");
	Jacketimg[3] = LoadGraph("�摜/�W���P�b�g/selectD.png");
	Jacketimg[4] = LoadGraph("�摜/�W���P�b�g/select2.png");
	Jacketimg[5] = LoadGraph("�摜/�W���P�b�g/select2.png");

	PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
}
//�����ɑI�ȉ�ʂƋ��L����CSelectNum

void Jacket::Finalize(){
	DeleteGraph(mImageHandle);
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	DeleteSoundMem(mSoundHandle);
}

//�X�V
void Jacket::Update() {
	if (counter < 255 && fade_flag == false) {  //�ŏ��̃t�F�[�h�C��
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g
		counter = counter - 5; 
	}


	if (counter > 254) {
		WaitTimer(700);
		fade_flag = true;
	}

	if (counter == 0 && fade_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		BaseScene::NowScene = eScene::eScene_Game;
	}
}

//�`��
void Jacket::Draw() {
	BaseScene::Draw();
	DrawRotaGraph(960, 500, 0.6, 0.0, Jacketimg[CSelectNum], TRUE);

	SelectTitle[CSelectNum].Draw();
	SelectDif[DSelectNum].Draw();

	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}