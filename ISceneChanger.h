#pragma once

//enumのみ
typedef enum {
	eScene_Title,  //タイトル画面
	eScene_Game,  //ゲーム画面
	eScene_Select,  //選曲画面
	eScene_Unlock, //アンロック画面
	eScene_Jacket, //ジャケット画面
	eScene_Result, //リザルト画面

	eScene_None,  //何もなし
}eScene;
