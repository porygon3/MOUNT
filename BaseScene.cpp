#include "BaseScene.h"
#include "DxLib.h"

int counter = 0;
bool fade_flag = false;
bool up_flag = false;
bool down_flag = false;
bool difup_flag = false;
bool difdown_flag = false;


int BaseScene::CSelectNum = 1;
int BaseScene::DSelectNum = 0;
int BaseScene::great_count = 0, BaseScene::ok_count = 0, BaseScene::bad_count = 0;
int BaseScene::highscore[6][4] = { {} };
int BaseScene::score[6][4] = { {} };
int BaseScene::clear_flag[6][4] = { {} };
int BaseScene::unlock_flag[6][4] = { {} };

eScene BaseScene::NowScene;

BaseScene::BaseScene(){
	mImageHandle	= 0;
	fade_flag		= false;
	up_flag			= false;
	down_flag		= false;
	tennmetu        = 0;
}

void BaseScene::Finalize() {
	DeleteGraph(mImageHandle);
}

void BaseScene::Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);
}
eScene BaseScene::GetNowScene(){
	return NowScene;
}