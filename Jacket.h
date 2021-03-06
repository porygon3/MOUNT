#pragma once
#include "BaseScene.h"


class Jacket : public BaseScene {

public :
	BaseMenu SelectTitle[SelectNum];
	BaseMenu SelectDif[Difficult];
	Jacket();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Jacket();

};