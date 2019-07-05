#include "Title.h"
#include "DxLib.h"

//�R���X�g���N�^--------------------------------------------------------------------------
Title::Title() : BaseScene() {
	Initialize();

}
//�f�X�g���N�^--------------------------------------------------------------------------
Title::~Title() {
	Finalize();
}

//������--------------------------------------------------------------------------
void Title::Initialize() {
	mImageHandle = LoadGraph("�摜/���/title.png");
	mSoundHandle = LoadSoundMem("��/����.wav");
}

void Title::Finalize() {
	DeleteGraph(mImageHandle);
	DeleteSoundMem(mSoundHandle);
}

//�X�V--------------------------------------------------------------------------
void Title::Update() {
	if (counter < 255 && fade_flag == false) {  //�ŏ��̃t�F�[�h�C��
	//(counter, counter, counter);
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g
		counter = counter - 5;
	}
	if (Keyboard::GetKey(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		fade_flag = true;
	}

	if (counter == 0 && fade_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		BaseScene::NowScene = eScene::eScene_Select;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}
}

//�`��--------------------------------------------------------------------------
void Title::Draw() {
	
	BaseScene::Draw();
	DrawString(40, 700, "EXIT [ESC]", GetColor(255, 255, 255));
	DrawString(800, 800, "- PUSH ENTER -", GetColor(255, 255, 255));
	SetFontSize(32);

	Fadeout();
}