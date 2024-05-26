/*
* @file		SelectEndState.cpp
* @brief	終了を選択した状態
* @author	Morita
* @date		2024/05/26
*/
#include "pch.h"

#include "SelectEndState.h"

SelectEndState::SelectEndState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f),
	m_flag(false)
{
}

SelectEndState::~SelectEndState()
{
}

void SelectEndState::Initialize()
{
	m_firstPosition = m_titleSelectManager->GetUIPosition()[0];
}

void SelectEndState::Update()
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
	

	//		上に移動
	if (m_direction)
	{
		m_titleSelectManager->CentreUP(m_direction, m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->CenterUnder(m_direction, m_time, TitleSelectManager::UIType::Play);

		m_titleSelectManager->UPUnder(m_direction, m_time, TitleSelectManager::UIType::Setting);
	}
	//		下に移動
	else
	{
		m_titleSelectManager->CentreUP(m_direction, m_time, TitleSelectManager::UIType::Setting);

		m_titleSelectManager->CenterUnder(m_direction, m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->UPUnder(m_direction, m_time, TitleSelectManager::UIType::Play);
	}

	if (m_time >= 1.0f)
	{
		m_flag = false;
		m_time = 0.0f;
	}
}

void SelectEndState::Render()
{
}

void SelectEndState::Finalize()
{
}
