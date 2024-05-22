/*
* @file		ScreenEffectManager.h
* @brief	スクリーンエフェクトのマネージャー
* @author	Morita
* @date		2024/05/22
*/

#pragma once

class ScreenEffectManager
{
public:

	//		コンストラクタ
	ScreenEffectManager();

	//		デストラクタ
	~ScreenEffectManager();

	//		初期化処理
	void Initialize();

	//		アップデート
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:



};
