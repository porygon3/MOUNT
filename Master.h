#pragma once

class Master {
public:
	Master() {};
	virtual ~Master() {}
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;  //�X�V�����͕K���p����Ŏ���
	virtual void Draw() = 0;  //�`�揈���͕K���p����Ŏ���


};