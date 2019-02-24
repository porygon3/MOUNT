#pragma once

class Master {
public:
	Master() {};
	virtual ~Master() {}
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;  //更新処理は必ず継承先で実装
	virtual void Draw() = 0;  //描画処理は必ず継承先で実装


};