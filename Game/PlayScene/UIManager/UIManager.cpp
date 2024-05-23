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
}

void UIManager::Update()
{
	m_clockManager->Update(m_gameManager);

	m_coolTime->Update();

	m_fadeIn->Update(m_gameManager);

	m_gameOver->Update();

	m_screenRay->Update();
}

void UIManager::FrontRender()
{
	m_clockManager->Render();

	m_coolTime->Render();

	m_screenRay->Render();
}

void UIManager::BackRender()
{
	m_gameOver->Render();

	m_fadeIn->Render();
}
