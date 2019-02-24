#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"

class Title : public BaseScene {

public:
	Title();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Title();

};