#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"

class Jacket : public BaseScene {

public :
	BaseMenu SelectTitle[6];
	BaseMenu SelectDif[4];
	Jacket();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Jacket();

};