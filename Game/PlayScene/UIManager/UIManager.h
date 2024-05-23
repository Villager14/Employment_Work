/*
* @file		UIManager.h
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Clock/ClockManager.h"

#include "CoolTime/CoolTime.h"

#include "Fade/FadeIn.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/PlayScene/UIManager/GameOver/GameOverManager.h"

#include "Game/PlayScene/UIManager/ScreenRay/ScreenRay.h"

class UIManager
{
public:
	//		コンストラクタ
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		デストラクタ
	~UIManager();

	//		初期処理
	void Initialize();

	void Update();

	void FrontRender();

	void BackRender();

private:
	//		時計の背景
	std::unique_ptr<ClockManager> m_clockManager;

	//		クールタイム
	std::unique_ptr<CoolTime> m_coolTime;

	//		フェード
	std::unique_ptr<FadeIn> m_fadeIn;
		
	//		ゲームオーバー
	std::unique_ptr<GameOverManager> m_gameOver;

	//		スクリーンのレイ
	std::unique_ptr<ScreenRay> m_screenRay;

	//		プレイヤーの情報を受け取る
	PlayerInformation* m_playerInformation;

	//		ゲームマネージャー
	GameManager* m_gameManager;
};