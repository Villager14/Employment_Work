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
	m_time(0.0f)
{
}

SelectEndState::~SelectEndState()
{
}

void SelectEndState::Initialize()
{
}

void SelectEndState::Update()
{
	//		キー入力処理
	m_titleSelectManager->InputKey();

	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
	ChangeSceneProcess();
}

void SelectEndState::Render()
{
}

void SelectEndState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectEndState::UIMove()
{
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetKeyInput()) return;

	//		経過時間
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		上に移動
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);
	}
	//		下に移動
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);
	}
}

void SelectEndState::ChangeSceneProcess()
{
	//		時間が１以下の場合処理をしない
	if (m_time < 1.0f)
	{
		//		キーボードの取得
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		ボタンの取得
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();
		
		//		スペースまたはマウス左クリックを押した場合
		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		ゲームを終了する
			PostQuitMessage(0);
		}
	}
	else
	{
		//		状態を選択する
		if (m_titleSelectManager->GetDirection())
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(TitleSelectManager::State::PlayState);
		}
		else
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(TitleSelectManager::State::SettingState);
		}
	}

}
