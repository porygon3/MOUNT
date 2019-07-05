#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"

class Result : public BaseScene {
private:
	int drawcount;
	int soundcount;
	bool flag;
	int Rscore;

	void ScoreRank() {
		//S�����N
		if (Rscore >= 950000) {
			DrawStringToHandle(1425, 800, "S", GetColor(255, 255, 0), fsHandle[2]);
			return;
		}

		//A�����N
		if (Rscore >= 900000) {
			DrawStringToHandle(1425, 800, "A", GetColor(255, 255, 0), fsHandle[2]);
			return;
		}

		//B�����N
		if (Rscore >= 800000) {
			DrawStringToHandle(1425, 800, "B", GetColor(130, 130, 130), fsHandle[2]);
			return;
		}

		//C�����N
		if (Rscore >= 700000) {
			DrawStringToHandle(1425, 800, "C", GetColor(150, 100, 0), fsHandle[2]);
			return;
		}

		//D�����N
		DrawStringToHandle(1425, 800, "D", GetColor(150, 100, 0), fsHandle[2]);

	}

public:
	//eScene next_scene;
	BaseMenu SelectTitle[SelectNum];
	BaseMenu SelectDif[Difficult];
	Result();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	~Result();

};