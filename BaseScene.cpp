#include "BaseScene.h"
#include "DxLib.h"

int timer = 70;
int counter = 0;
int counter2 = Illum;
bool fade_flag = false;
bool flash_flag = false;
bool up_flag = false;
bool down_flag = false;
bool difup_flag = false;
bool difdown_flag = false;


int BaseScene::CSelectNum = 1;
int BaseScene::DSelectNum = 0;
int BaseScene::great_count = 0, BaseScene::ok_count = 0, BaseScene::bad_count = 0;
int BaseScene::highscore[SelectNum][Difficult] = { {} };
int BaseScene::score[SelectNum][Difficult] = { {} };
int BaseScene::clear_flag[SelectNum][Difficult] = { {} };
int BaseScene::unlock_flag[SelectNum][Difficult] = { {} };
int BaseScene::GaugeEnergie = 100;

eScene BaseScene::NowScene;


BaseScene::BaseScene(){
	mImageHandle = 0;
	fade_flag = false;
	flash_flag = false;
	up_flag	= false;
	down_flag = false;
	tennmetu = 0;
}

void BaseScene::Finalize() {
	mImageHandle = 0;
	fade_flag = false;
	flash_flag = false;
	up_flag = false;
	down_flag = false;
	tennmetu = 0;
}

void BaseScene::Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);
}
eScene BaseScene::GetNowScene(){
	return NowScene;
}