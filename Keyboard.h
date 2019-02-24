#pragma once
#include <DxLib.h>
class Keyboard
{
private:
	static char tmpKey[256];
	static  int Key[256];
public:
	static void Update();
	static int GetKey(int);
};

