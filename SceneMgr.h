#pragma once

#include "ISceneChanger.h"
#include "BaseScene.h"
#include <assert.h>


class SceneMgr:public Master{
public:

	SceneMgr();
	~SceneMgr();
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void ChangeScene();

private:

	BaseScene* scene;
	eScene es;		//ëOÇÃÉVÅ[Éì
};