#include "Keyboard.h"

char Keyboard::tmpKey[256];
int Keyboard::Key[256];

void Keyboard::Update() {
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] == 1) Key[i]++;
		else Key[i] = 0;
	}
}
int Keyboard::GetKey(int keycode){
	return Key[keycode];
}