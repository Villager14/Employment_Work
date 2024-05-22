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

#include "Game/PlayScene/Player/Player.h"

class UIManager
{
public:
	//		コンストラクタ
	UIManager(Player* player);

	//		デストラクタ
	~UIManager();

	//		初期処理
	void Initialize();

	void Update();

	void Render();

private:
	//		時計の背景
	std::unique_ptr<ClockManager> m_clockManager;

	//		クールタイム
	std::unique_ptr<CoolTime> m_coolTime;

	std::unique_ptr<FadeIn> m_fadeIn;

	//		プレイヤーの情報を受け取る
	Player* m_player;
};