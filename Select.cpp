#include "Select.h"
#include "DxLib.h"


using namespace std;

//�R���X�g���N�^--------------------------------------------------------------------------
Select::Select() : BaseScene() {

	Initialize();

	//25���ύX����
	//( x, y, BPM, �^�C�g��, ��Փx1, ��Փx2, ��Փx3, ��Փx4)
	SelectTitle[0].SMake(SStart, 100, 280,"�n�C�X�s2000",1,2,4,6);  //�\���̂ɒ��g��^����
	SelectTitle[1].SMake(SStart - 25, 350, 160,"Heaven helps you",1,3,5,7);
	SelectTitle[2].SMake(SStart - 50, 600, 250,"UN Equald",3,5,7,9);
	SelectTitle[3].SMake(SStart - 75, 850, 178,"Gear",2,4,6,8);
	SelectTitle[4].SMake(SStart - 100, 1100, 165,"INVASION",3,5,7,10);
	SelectTitle[5].SMake(SStart + 25, -150, 0,"----------EXIT----------",0,0,0,0);
	upcount = 0;
	downcount = 0;

	SelectDif[0].DMake(400, 900, "NOV");
	SelectDif[1].DMake(575, 900, "ADV");
	SelectDif[2].DMake(750, 900, "DIF");
	SelectDif[3].DMake(925, 900, "EXT");
	difupcount = 0;
	difdowncount = 0;

	string text_name;
	text_name = "����/test" + to_string(CSelectNum) + "," + to_string(DSelectNum) + ".txt";

	ifstream n_file(text_name);
	if (n_file.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DxLib_End();
	}
	else {
		string str;


		getline(n_file, str); //�^�C�g���Ȃǂ�ǂݍ���
		f_title = str;
		getline(n_file, str);
		f_bpm = str;
		BPM = stoi(f_bpm);
		getline(n_file, str);
		f_beat = str;
		Beat = stoi(f_beat);
		getline(n_file, str);
		f_speed = str;
		Speed = stoi(f_speed);
	}
}
Select::~Select(){
	Finalize();
}

//������--------------------------------------------------------------------------
void Select::Initialize() {
	mImageHandle = LoadGraph("�摜/���/select.png");
	mSoundHandle = LoadSoundMem("��/�ړ�.wav");
	
	CSelectNum = 1;
	DSelectNum = 0;
	DifCount = 0;
	great_count = 0, ok_count = 0, bad_count = 0;

	music_flag = 1;

	for (int i = 0; i < SelectNum; i++) {
		u_flag[i] = 0;;
	}

	for (int i = 0; i < UNLOCK; i++) {
		unlock_flag[1][i] = 1;
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
	Otherimg[7] = 0;
	Otherimg[8] = 0;
	Otherimg[9] = 0;

	Music[0] = 0;
	Music[1] = LoadSoundMem("��/��/ճ�׳��i����ճ�׳��j.wav");
	Music[2] = 0;
	Music[3] = 0;
	Music[4] = 0;
	Music[5] = 0;

	SE[0] = LoadSoundMem("��/�ړ�.wav");
	SE[1] = LoadSoundMem("��/����.wav");



	//�A�����b�N��ʂ����I����������
	clear_flag[1][0] = 1;

}

//�������J��--------------------------------------------------------------------------
void Select::Finalize() {
	DeleteGraph(mImageHandle);
	for (int i = 0; i < SelectNum; i++) {
		DeleteGraph(Jacketimg[i]);
	}
	for (int i = 0; i < Other; i++) {
		DeleteGraph(Otherimg[i]);
	}
	for (int i = 0; i < SelectNum; i++) {
		DeleteSoundMem(Music[i]);
	}
	for (int i = 0; i < SENum; i++) {
		DeleteSoundMem(SE[i]);
	}
	
	DeleteSoundMem(mSoundHandle);
}

//�X�V--------------------------------------------------------------------------
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


	if (counter2 < 255 && flash_flag == false) {  //�ŏ��̃t���b�V���C��
		counter2 = counter2 + 15;
	}
	else if (counter2 > 0 && flash_flag == true) { //�؂�ւ��̃t���b�V���A�E�g
		counter2 = counter2 - 15;
	}

	
	if (counter == 0 && fade_flag == true) { //�����Ńt�F�[�h�A�E�g�Ő^���Â̂Ƃ��ɃV�[����ւ���
		if (CSelectNum != 5) {
			BaseScene::NowScene = eScene::eScene_Jacket;
		}
		else {
			BaseScene::NowScene = eScene::eScene_Title;
		}
	}


	if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
		if (unlock_flag[CSelectNum][DSelectNum] == 0) {
			flash_flag = true;
		}
	}


	if (counter2 == 0 && flash_flag == true) {
		BaseScene::NowScene = eScene::eScene_Unlock;
	}


	//�I�Ȉړ�
	if (Keyboard::GetKey(KEY_INPUT_DOWN) == 1 && upcount == 0) {
		for (int i = 0; i < sizeof(Music) / sizeof(int); i++) {
			StopSoundMem(Music[i]);
		}
		down_flag = true;
		PlaySoundMem(SE[0], DX_PLAYTYPE_BACK);
	}
	if (Keyboard::GetKey(KEY_INPUT_UP) == 1 && downcount == 0) {
		for (int i = 0; i < sizeof(Music) / sizeof(int); i++) {
			StopSoundMem(Music[i]);
		}
		up_flag = true;
		PlaySoundMem(SE[0], DX_PLAYTYPE_BACK);
	}
	if (Keyboard::GetKey(KEY_INPUT_RIGHT) == 1 && DifCount < 525) {
		difup_flag = true;
		PlaySoundMem(SE[0], DX_PLAYTYPE_BACK);
	}
	if (Keyboard::GetKey(KEY_INPUT_LEFT) == 1 && DifCount > 0) {
		difdown_flag = true;
		PlaySoundMem(SE[0], DX_PLAYTYPE_BACK);
	}

	//��������
	if (music_flag == 1) {
		PlaySoundMem(Music[CSelectNum], DX_PLAYTYPE_BACK);
		music_flag = 0;
	}

	// �͂ݏo������
	if (CSelectNum > SelectNum - 1) CSelectNum = 0;
	if (CSelectNum < 0) CSelectNum = SelectNum - 1;

	if (DSelectNum > Difficult) DSelectNum = Difficult;
	if (DSelectNum < 0) DSelectNum = 0;


	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {  //���ׂĂ��I����
		exit(1);
	}

	
}


//�`��--------------------------------------------------------------------------
void Select::Draw() {
	BaseScene::Draw();  //�e�N���X�̕`�惁�\�b�h���Ă�

	tennmetu++;

	DrawString(465, 10, "Select Music", GetColor(255, 255, 255));

	DrawRotaGraph(600, 500, 0.5, 0.0, Otherimg[DSelectNum], TRUE); //�W���P�b�g�̌���\��
	
	DrawRotaGraph(600, 500, 0.4, 0.0, Jacketimg[CSelectNum], TRUE); //���ꂼ��̃W���P�b�g��\��

	DrawRotaGraph3(-500, 400, 0, 0, 1.0, 1.0, 0.0, Otherimg[5], TRUE);
	DrawRotaGraph3(-500, -600, 0, 0, 1.0, 1.0, 0.0, Otherimg[6], TRUE);

	//�Q�[�W�G�l���M�[�\��
	DrawRotaGraph3(100, 200, 0, 0, 0.1, 0.05, 0.0, Otherimg[0], TRUE);
	DrawString(150, 225, "GE", GetColor(255, 255, 255));
	DrawRotaGraph3(150, 225, 0, 0, 0.15, 0.05, 0.0, Otherimg[0], TRUE);
	DrawFormatString(200, 240, 0xff00ff, "%d", GaugeEnergie);
	DrawRotaGraph3(120, 290, 0, 0, 0.1, 0.0001 * GaugeEnergie, 0.0, Otherimg[2], TRUE);

	if (CSelectNum != 5) {
		DrawFormatString(200, 100, 0xffffff, "%s", SelectTitle[CSelectNum].name);
		DrawString(300, 200, "BPM : ", GetColor(255, 255, 255));
		DrawFormatString(400, 200, 0xffffff, "%d", SelectTitle[CSelectNum].bpm);
		DrawString(250, 950, "LEVEL : ", GetColor(255, 255, 255));

		DrawString(400, 760, "HighScore", GetColor(255, 255, 255));
		DrawFormatString(780, 760, 0xff00ff, "%d", highscore[CSelectNum][DSelectNum]);

		//��Փx��\��
		for (int i = 0; i < Difficult; i++) {
			DrawFormatString(400 + (175 * i), 950, 0xffffff, "%d", SelectTitle[CSelectNum].level[i]);
		}
	}
	
	if (CSelectNum < SelectNum - 1) {
		if (unlock_flag[CSelectNum][DSelectNum] == 0) {

			for (int i = 0; i < 10; i++) {
				DrawRotaGraph(600, 500, 0.4, 0.0, Otherimg[3], TRUE);

			}

			UnlockDraw();
		}
	}

	DrawRotaGraph(1350, 680, 0.9, 0.0, Otherimg[4], TRUE);

	//�I�Ȉړ�
	if (upcount < 25 && up_flag == true)
	{
		upcount++;

		for (int i = 0; i < SelectNum; i++) {
			SelectTitle[i].Sub();
		}
		if (upcount >= 25) {
			up_flag = false;
			upcount = 0;
			CSelectNum++;
			music_flag = 1;
		}
	}

	if (downcount < 25 && down_flag == true){

		downcount++;

		for (int i = 0; i < SelectNum; i++) {
			SelectTitle[i].Add();
		}
		if (downcount >= 25) {
			down_flag = false;
			downcount = 0;
			CSelectNum--;
			music_flag = 1;
		}
	}

	for (int i = 0; i < SelectNum; i++) {
		SelectTitle[i].Draw();
	}


	//��Փx
	if (CSelectNum != 5) {
		for (int i = 0; i < Difficult; i++) {
			SelectDif[i].Draw();
		}
		//�J�[�\��
		DrawString(Dbox + DifCount, 900, "�y     �z", GetColor(255, 0, 100));
	}
	

	//��Փx�ړ�
	if (difupcount < 175 && difup_flag == true){

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

	Fadeout();
	Flash();

	
}