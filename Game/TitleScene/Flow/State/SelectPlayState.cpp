/*
* @file		SelectPlayerState.cpp
* @brief	プレイを選択した状態
* @author	Morita
* @date		2024/05/25
*/

#include "pch.h"

#include "SelectPlayState.h"

SelectPlayState::SelectPlayState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{

}

SelectPlayState::~SelectPlayState()
{
}

void SelectPlayState::Initialize()
{
	m_titleFlow->AnimationObserver()->PlayAnimation();
}

void SelectPlayState::Update()
{
	m_titleFlow->InputKey();

	//		シーン切り替え処理
	ChangeSceneProcess();
}

void SelectPlayState::Finalize()
{
	m_titleFlow->SelectionInfromationReset();
	//m_titleSelectManager->GetInformation()->SetKeyInput(false);
}

void SelectPlayState::ChangeSceneProcess()
{
	if (m_titleFlow->SelectionBarMoveProcess())
	{
		if (m_titleFlow->GetSelectionBarMoveDirection() == TitleFlowManager::SelectionBarMoveDirection::Up)
		{
			//		設定選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::SettingState);
		}
		else
		{
			//		終了選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::EndState);
		}

		return;
	}

	if (m_titleFlow->GetSelectionBarMoveDirection() == TitleFlowManager::SelectionBarMoveDirection::Not)
	{
		//		キーボードの取得
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		ボタンの取得
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			//		終了選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::ChangState);
		}
	}
}
