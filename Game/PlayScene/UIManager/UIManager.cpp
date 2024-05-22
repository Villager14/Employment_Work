/*
* @file		UIManager.cpp
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "UIManager.h"

UIManager::UIManager(Player* player)
	:
	m_player(player)
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
}

void UIManager::Update()
{
	m_clockManager->Update();

	m_coolTime->Update();

	m_fadeIn->Update();
}

void UIManager::Render()
{
	m_clockManager->Render();

	m_coolTime->Render();

	m_fadeIn->Render();
}
