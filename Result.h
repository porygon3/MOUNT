#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"

class Result : public BaseScene {

private:
	int drawcount;

public:
	//eScene next_scene;
	BaseMenu SelectTitle[6];
	BaseMenu SelectDif[4];
	Result();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Result();

};