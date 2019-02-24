#include "Select.h"
#include "DxLib.h"

Select::Select() : BaseScene() {

	SelectTitle[0].SMake(1300, 100, 280,"�n�C�X�s2000",1,2,4,6);  //5�̍\���̂ɒ��g��^����
	SelectTitle[1].SMake(1275, 350, 160,"Heaven helps you",1,3,5,7);
	SelectTitle[2].SMake(1250, 600, 250,"UN Equald",3,5,7,9);
	SelectTitle[3].SMake(1225, 850, 178,"Gear",2,4,6,8);
	SelectTitle[4].SMake(1200, 1100, 165,"INVASION",3,5,7,10);
	SelectTitle[5].SMake(1325, -150, 0,"----------EXIT----------",0,0,0,0);
	upcount = 0;
	downcount = 0;

	SelectDif[0].DMake(400, 900, "NOV");
	SelectDif[1].DMake(575, 900, "ADV");
	SelectDif[2].DMake(750, 900, "DIF");
	SelectDif[3].DMake(925, 900, "EXT");
	difupcount = 0;
	difdowncount = 0;
}
Select::~Select(){}

//������
void Select::Initialize() {
	mImageHandle = LoadGraph("�摜/���/select.png");
	mSoundHandle = LoadSoundMem("��/�ړ�.wav");
	
	CSelectNum = 1;
	DSelectNum = 0;
	DifCount = 0;
	great_count = 0, ok_count = 0, bad_count = 0;

	for (int i = 0; i < 3; i++) {
		unlock_flag[1][i] = 1;
	}
	//���ʂɂǂ̓�Փx�̃N���A�ł��ō���Փx�����ւł���悤�ɂȂ��Ă���
	for (int i = 0; i < 3; i++) {
		if (clear_flag[CSelectNum][i] == 1) {
			unlock_flag[CSelectNum][3] = 1;
		}
	}

	Jacketimg[0] = LoadGraph("�摜/�W���P�b�g/RH.png");
	Jacketimg[1] = LoadGraph("�摜/�W���P�b�g/hellnear.png");
	Jacketimg[2] = LoadGraph("�摜/�W���P�b�g/unequald_j.png");
	Jacketimg[3] = LoadGraph("�摜/�W���P�b�g/darkRL.png");
	Jacketimg[4] = LoadGraph("�摜/�W���P�b�g/invasion.png");
	Jacketimg[5] = LoadGraph("�摜/���/select2.png");
	

	Otherimg[0] = LoadGraph("�摜/���/select2.png");
	Otherimg[1] = LoadGraph("�摜/���/select2yellow.png");
	Otherimg[2] = LoadGraph("�摜/���/select2red.png");
	Otherimg[3] = LoadGraph("�摜/���/select2black.png");
	Otherimg[4] = LoadGraph("�摜/���/unit.png");
	Otherimg[5] = LoadGraph("�摜/���/part.png");
	Otherimg[6] = LoadGraph("�摜/���/part2.png");

	SE[0] = LoadSoundMem("��/�ړ�.wav");
	SE[1] = LoadSoundMem("��/����.wav");

	
}

void Select::Finalize() {
	DeleteGraph(mImageHandle);
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	for (int i = 0; i < 6; i++) {
		DeleteGraph(Otherimg[i]);
	}
	
	DeleteSoundMem(mSoundHandle);
	DeleteSoundMem(SE[0]);
	DeleteSoundMem(SE[1]);
}

//�X�V
void Select::Update() {
	if (counter < 255 && fade_flag == false) {  //�ŏ��̃t�F�[�h�C��
		counter = counter + 5;
	}
	else if (counter > 0 && fade_flag == true) { //�؂�ւ��̃t�F�[�h�A�E�g
		counter = counter - 5;
	}


	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		if (unlock_flag[CSelectNum][DSelectNum] == 1) {
			fade_flag = true;
		}
		else if (CSelectNum == 5) {
			fade_flag = true;
		}
	}

	
	
	if (counter == 0 && fade_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		if (CSelectNum != 5) {
			BaseScene::NowScene = eScene::eScene_Jacket;
		}
		else {
			BaseScene::NowScene = eScene::eScene_Title;
		}
	}


	{
		if (Keyboard::GetKey(KEY_INPUT_DOWN) == 1 && upcount == 0) {
			
			down_flag = true;
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}
		if (Keyboard::GetKey(KEY_INPUT_UP) == 1 && downcount == 0) {
			
			up_flag = true;
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}
		if (Keyboard::GetKey(KEY_INPUT_RIGHT) == 1 && DifCount < 525) {

			difup_flag = true;
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}
		if (Keyboard::GetKey(KEY_INPUT_LEFT) == 1 && DifCount > 0) {

			difdown_flag = true;
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK);
		}
	}

	// �͂ݏo������
	{
		if (CSelectNum > 5) CSelectNum = 0;
		if (CSelectNum < 0) CSelectNum = 5;
	}
	{
		if (DSelectNum > 4) DSelectNum = 4;
		if (DSelectNum < 0) DSelectNum = 0;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}

}


//�`��
void Select::Draw() {
	BaseScene::Draw();  //�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(465, 10, "Select Music", GetColor(255, 255, 255));

	DrawRotaGraph(600, 500, 0.5, 0.0, Otherimg[DSelectNum], TRUE); //�W���P�b�g�̌���\��
	
	DrawRotaGraph(600, 500, 0.4, 0.0, Jacketimg[CSelectNum], TRUE); //���ꂼ��̃W���P�b�g��\��

	DrawRotaGraph3(-200, 400, 0, 0, 1.0, 1.0, 0.0, Otherimg[5], TRUE);
	DrawRotaGraph3(-500, -600, 0, 0, 1.0, 1.0, 0.0, Otherimg[6], TRUE);

	if (CSelectNum != 5) {
		DrawFormatString(200, 100, 0xffffff, "%s", SelectTitle[CSelectNum].name);
		DrawString(300, 200, "BPM : ", GetColor(255, 255, 255));
		DrawFormatString(400, 200, 0xffffff, "%d", SelectTitle[CSelectNum].bpm);
		DrawString(250, 950, "LEVEL : ", GetColor(255, 255, 255));

		DrawString(400, 760, "HighScore", GetColor(255, 255, 255));
		DrawFormatString(780, 760, 0xff00ff, "%d", highscore[CSelectNum][DSelectNum]);
		for (int i = 0; i < 4; i++) {
			DrawFormatString(400 + (175 * i), 950, 0xffffff, "%d", SelectTitle[CSelectNum].level[i]);
		}
	}
	
	if (CSelectNum < 5) {
		if (unlock_flag[CSelectNum][DSelectNum] == 0) {

			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(600, 500, 0.4, 0.0, Otherimg[3], TRUE);

			}
			DrawString(550, 500, "LOCK", GetColor(255, 255, 255));
		}


	}

	DrawRotaGraph(1350, 680, 0.9, 0.0, Otherimg[4], TRUE);

	//�I�Ȉړ�
	if (upcount < 25 && up_flag == true)
	{
		//x--;
		upcount++;
	//	y = y - 10;
		for (int i = 0; i < 6; i++) {
			SelectTitle[i].Sub();
		}
		if (upcount >= 25) {
			up_flag = false;
			upcount = 0;
			CSelectNum++;
		}
	}
	if (downcount < 25 && down_flag == true)
	{
		downcount++;
		for (int i = 0; i < 6; i++) {
			SelectTitle[i].Add();
		}
		if (downcount >= 25) {
			down_flag = false;
			downcount = 0;
			CSelectNum--;
		}
	}

	for (int i = 0; i < 6; i++) {
		SelectTitle[i].Draw();
	}


	//��Փx
	if (CSelectNum != 5) {
		for (int i = 0; i < 4; i++) {
			SelectDif[i].Draw();
		}
		//�J�[�\��
		DrawString(350 + DifCount, 900, "�y     �z", GetColor(255, 0, 100));
	}
	

	//��Փx�ړ�
	if (difupcount < 175 && difup_flag == true)
	{

			difupcount += 25;
			DifCount += 25;
		if (difupcount >= 175) {
			difup_flag = false;
			difupcount = 0;
			DSelectNum++;
		}
	}
	if (difdowncount < 175 && difdown_flag == true)
	{
			difdowncount += 25;
			DifCount -= 25;
		if (difdowncount >= 175) {
			difdown_flag = false;
			difdowncount = 0;
			DSelectNum--;
		}
	}

	SetFontSize(32);
	if (counter < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - counter);
		DrawBox(0, 0, 1920, 1080, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}