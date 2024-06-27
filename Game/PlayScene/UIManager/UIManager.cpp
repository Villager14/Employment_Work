/*
* @file		UIManager.cpp
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

UIManager::UIManager(PlayerInformation* playerInformation,
					 GameManager* gameManager)
	:
	m_playerInformation(playerInformation),
	m_gameManager(gameManager)
{
}

UIManager::~UIManager()
{
}

void UIManager::Initialize()
{
	//		時計の背景の生成
	m_clockManager = std::make_unique<ClockManager>();

	//		時計の背景の初期化
	m_clockManager->Initialize();

	//		クールタイムの生成
	m_coolTime = std::make_unique<CoolTime>();

	//		クールタイムの初期化
	m_coolTime->Initialize();

	//		フェードインの生成
	m_fadeIn = std::make_unique<FadeIn>();

	//		フェードインの初期化
	m_fadeIn->Initialize();

	//		ゲームーオーバーの生成
	m_gameOver = std::make_unique<GameOverManager>(m_gameManager);

	//		ゲームオーバーの初期化
	m_gameOver->Initialize();

	//		スクリーンの例の生成
	m_screenRay = std::make_unique<ScreenRay>(m_gameManager);

	//		スクリーンの初期化
	m_screenRay->Initialize();

	//		ゲームクリアマネージャーの生成
	m_clearManager = std::make_unique<GameClearManager>(m_gameManager);

	//		ゲームクリアマネージャーの初期化
	m_clearManager->Initialize();

	//		集中線の生成
	m_concentrationLine = std::make_unique<ConcentrationLineManager>();

	//		集中線の初期化
	m_concentrationLine->Initialize();
}

void UIManager::Update()
{
	//		時間の更新
	m_clockManager->Update(m_gameManager);

	//		ダッシュクールタイムの更新
	m_coolTime->Update(m_playerInformation);

	//		フェードの更新
	m_fadeIn->Update(m_gameManager);

	//		ゲームオーバーの更新
	m_gameOver->Update();

	//		スクリーンの線の更新
	m_screenRay->Update();

	//		集中線の更新
	m_concentrationLine->Update();
}

void UIManager::FrontRender()
{
	//		集中線の描画
	m_concentrationLine->Render();

	//		時計の描画
	m_clockManager->Render();

	//		ダッシュクールタイムの描画
	m_coolTime->Render();

	//		スクリーンの線の描画
	m_screenRay->Render();

	//		ゲームクリアマネージャーの描画
	m_clearManager->Render();
}

void UIManager::BackRender()
{
	//		ゲームーバーの描画
	m_gameOver->Render();

	//		ゲームクリアマネージャーの更新
	m_clearManager->Update();

	//		フェードインの描画
	m_fadeIn->Render();
}
