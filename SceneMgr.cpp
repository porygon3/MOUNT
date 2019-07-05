#include "DxLib.h"
#include "Select.h"
#include "Game.h"
#include "Title.h"
#include "Jacket.h"
#include "Result.h"
#include "Unlock.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr(){
	scene = new Title();
	Initialize();
}
SceneMgr::~SceneMgr() {
	Finalize();
	delete scene;
}


void SceneMgr::Initialize() {
	scene->Initialize();
}
void SceneMgr::Finalize() {
	scene->Finalize();
}

void SceneMgr::ChangeScene() {

	//íœ
	if (scene != nullptr) {
		Finalize();
		delete scene;
		scene = nullptr;
	}

	switch (scene->GetNowScene()) {  //¡‚ÌƒV[ƒ“‚Í‰½‚©
	case eScene::eScene_Title:
		scene = new Title();
		break;
	case eScene::eScene_Select:
		scene = new Select();
		break;
		case eScene::eScene_Unlock:
		scene = new Unlock();
		break;
	case eScene::eScene_Jacket:
		scene = new Jacket();
		break;
	case eScene::eScene_Game:
		scene = new Game();
		break;
	case eScene::eScene_Result:
		scene = new Result();
		break;
	default:
		assert(0);
		break;
	}
	Initialize();
}

void SceneMgr::Update() {
	if (es != scene->GetNowScene()) {
		es = scene->GetNowScene();
		ChangeScene();
	}
	scene->Update();
}
void SceneMgr::Draw() {
	scene->Draw();
}
