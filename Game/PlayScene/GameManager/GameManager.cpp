/*
* @file		GameManager.cpp
* @brief	ゲームマネージャー
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "GameManager.h"

GameManager::GameManager()
	:
	m_gameStartJudgement(false),
	m_deathJudgement(false),
	m_revivalJudgement(false),
	m_goalJudgement(false),
	m_endJudgement(false),
	m_nextSceneJudgement(false),
	m_time(0.0f),
	m_deathCount(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::Update()
{

	if (!m_deathJudgement) return;

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		マウスの取得
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Spaceまたは左クリックを押した場合復活する
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		m_revivalJudgement = true;
	}
}
