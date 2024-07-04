/*
* @file		StartSceneState.cpp
* @brief	開始した状態
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "StartSceneState.h"

StartSceneState::StartSceneState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

StartSceneState::~StartSceneState()
{
}

void StartSceneState::Initialize()
{
	m_time = 0.0f;
}

void StartSceneState::Update()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		ゲーム開始時の音量のボリューム調整
	MusicLibrary::GetInstance()->SceneLerpVolume(m_time);

	if (m_time >= 1.0f)
	{
		//		開始状態にする
		m_titleSelectManager->ChangeState(TitleSelectManager::State::PlayState);
	}
}

void StartSceneState::Render()
{
	m_titleSelectManager->FadeViewProcess(m_time);
}

void StartSceneState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}
