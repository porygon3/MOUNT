#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"

class Select : public BaseScene {
private:
	int x = 0;
	int y = 0;
	BaseMenu SelectTitle[6]; //  基底で作った構造体を6つ宣言

	BaseMenu SelectDif[4];
	
public:
	Select();
	int upcount;
	int downcount;
	int difupcount;
	int difdowncount;

	int DifCount;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	
	~Select();

};
