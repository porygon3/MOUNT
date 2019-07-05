#pragma once
#include "BaseScene.h"

class Unlock : public BaseScene {
private:
	int timer;

public:
	BaseMenu SelectTitle[SelectNum];
	BaseMenu SelectDif[Difficult];
	Unlock();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Unlock();

};