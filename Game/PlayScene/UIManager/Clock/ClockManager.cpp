/*
* @file		ClockManager.h
* @brief	UI時計のマネージャー
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockManager.h"

ClockManager::ClockManager()
	:
	m_elapsedTime(0.0f)
{
}

ClockManager::~ClockManager()
{
}

void ClockManager::Initialize()
{
	//		時計の背景の生成
	m_clockBackGround = std::make_unique<ClockBackGround>();

	//		時計の背景の初期化
	m_clockBackGround->Initialize();

	//		時計の数字の生成
	m_clockTime = std::make_unique<ClockTime>();

	//		時計の数字の初期化
	m_clockTime->Initialize();
}

void ClockManager::Update(GameManager* gameManager)
{
	if (gameManager->GetGameStartJudgement() && !gameManager->GetDeathJudgement() && !gameManager->GetGoalJudgement())
	{
		//		経過時間
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();
	}

	gameManager->SetTime(m_elapsedTime);

	//		背景の更新
	m_clockBackGround->Update(m_elapsedTime);

	//		数字の更新
	m_clockTime->Update(m_elapsedTime);
}

void ClockManager::Render()
{
	//		背景の更新
	m_clockBackGround->Render();

	//		数字の更新
	m_clockTime->Render();
}

void ClockManager::Finalize()
{
}
