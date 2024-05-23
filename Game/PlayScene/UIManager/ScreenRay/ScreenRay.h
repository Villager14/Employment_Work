/*
* @file		ScreenRay.h
* @brief	ゲームオーバーマネージャー
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

class ScreenRay
{
public:
	//		コンストラクタ
	ScreenRay(GameManager* gameManager);

	//		デストラクタ
	~ScreenRay();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

	//		ゲームオーバーの描画
	std::unique_ptr<UIRender> m_screenRay;
};