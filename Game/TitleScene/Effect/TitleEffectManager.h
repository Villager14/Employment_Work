/*
* @file		TitleEffectManager.cpp
* @brief	タイトルエフェクトマネージャー
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "Effect/Effect/DigitalRain/DegitalRain.h"

class TitleEffectManager
{
public:

	//		コンストラクタ
	TitleEffectManager();

	//		デストラクタ
	~TitleEffectManager();

	//		初期化処理
	void Initialize();
	
	//		更新処理
	void Update();

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

private:

	//		デジタル雨
	std::unique_ptr<DegitalRain> m_degitalRanin;

};