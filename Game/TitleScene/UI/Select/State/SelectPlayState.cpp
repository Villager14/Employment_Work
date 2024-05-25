/*
* @file		SelectPlayerState.cpp
* @brief	プレイを選択した状態
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "SelectPlayState.h"

SelectPlayState::SelectPlayState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f),
	m_flag(false)
{
}

SelectPlayState::~SelectPlayState()
{
}

void SelectPlayState::Initialize()
{
	m_firstPosition = m_titleSelectManager->GetUIPosition()[0];
}

void SelectPlayState::Update()
{
	DirectX::SimpleMath::Vector2 position = m_titleSelectManager->GetUIPosition()[0];

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	if (keyboard.IsKeyPressed(DirectX::Keyboard::W))
	{
		if (!m_flag)
		{
			m_flag = true;
			m_direction = true;
		}
	}
	
	if (keyboard.IsKeyPressed(DirectX::Keyboard::S))
	{
		if (!m_flag)
		{
			m_flag = true;
			m_direction = false;
		}
	}

	if (!m_flag) return;

	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 7.0f;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);
	

	m_titleSelectManager->CentreUP(m_direction, m_time, TitleSelectManager::UIType::Play);

	m_titleSelectManager->CenterUnder(m_direction, m_time, TitleSelectManager::UIType::Setting);

	m_titleSelectManager->UPUnder(m_direction, m_time, TitleSelectManager::UIType::End);

	if (m_time >= 1.0f)
	{
		m_flag = false;
		m_time = 0.0f;
	}
}

void SelectPlayState::Render()
{
}

void SelectPlayState::Finalize()
{
}
