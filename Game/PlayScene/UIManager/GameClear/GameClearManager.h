/*
* @file		GameOverManager.h
* @brief	ゲームオーバーマネージャー
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/UIRender.h"

#include "../CenterShader.h"

#include "../GlitchShader.h"

class GameClearManager
{
public:
	//		コンストラクタ
	GameClearManager(GameManager* gameManager);

	//		デストラクタ
	~GameClearManager();

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
	std::vector<std::unique_ptr<UIRender>> m_gameOverRender;

	//		中心シェーダー
	std::unique_ptr<CenterShader> m_centerShader;

	//		グリッチシェーダー
	std::unique_ptr<GlitchShader> m_glitchShader;

	//		経過時間
	float m_elapsedTime;

	//		スケール
	float m_scale;

	//		移動量
	float m_move;
};