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
	m_time(0.0f)
{
}

SelectPlayState::~SelectPlayState()
{
}

void SelectPlayState::Initialize()
{
}

void SelectPlayState::Update()
{
	//		キー入力処理
	m_titleSelectManager->InputKey();

	//		UIの移動処理
	UIMove();

	//		シーン切り替え処理
	ChangeSceneProcess();
}

void SelectPlayState::Render()
{
}

void SelectPlayState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectPlayState::UIMove()
{
	//		キー処理がなかった場合処理をしない
	if (!m_titleSelectManager->GetKeyInput()) return;

	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		上に移動
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);
	}
	//		下に移動
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);
	}
}

void SelectPlayState::ChangeSceneProcess()
{
	//		時間が１以下の場合処理をしない
	if (m_time < 1.0f)
	{
		//		キーボードの取得
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		ボタンの取得
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		プレイシーンに切り替える
			m_titleSelectManager->SetChangeSceneJudgement(true);
		}
	}
	else
	{

		//		移動方向によって状態を切り替える
		if (!m_titleSelectManager->GetDirection())
		{
			//		終了選択状態にする
			m_titleSelectManager->ChangeState(m_titleSelectManager->GetSelectEndState());
		}
		else
		{
			//		設定選択状態にする
			m_titleSelectManager->ChangeState(m_titleSelectManager->GetSelectSettingState());
		}
	}
}
