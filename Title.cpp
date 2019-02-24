#include "Title.h"
#include "DxLib.h"

Title::Title() : BaseScene() {


}
Title::~Title() {}

//������
void Title::Initialize() {
	mImageHandle = LoadGraph("�摜/���/title.png");
}

void Title::Finalize() {
	DeleteGraph(mImageHandle);
}

//�X�V
void Title::Update() {
	if (counter < 255 && fade_flag == false) {  //�ŏ��̃t�F�[�h�C��
	//	
		(counter, counter, counter);
		counter=counter+5;
	}
	else if (counter > 0 && fade_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g
		counter=counter-5;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		fade_flag = true;
	}

	if (counter == 0 && fade_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		BaseScene::NowScene = eScene::eScene_Select;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}
}

//�`��
void Title::Draw() {
	
	BaseScene::Draw();
	DrawString(40, 700, "EXIT [ESC]", GetColor(255, 255, 255));
	DrawString(800, 800, "- PUSH ENTER -", GetColor(255, 255, 255));
	SetFontSize(32);
	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}