/*
* @file		SelectEndState.cpp
* @brief	終了を選択した状態
* @author	Morita
* @date		2024/05/26
*/
#include "pch.h"

#include "SelectEndState.h"

#include "../TitleFlowManager.h"

SelectEndState::SelectEndState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{
}

SelectEndState::~SelectEndState()
{
}

void SelectEndState::Initialize()
{
	//m_titleSelectManager->GetAnimation()->ChangeState(AnimationManager::Upright);
	m_titleFlow->AnimationObserver()->ExitAnimation();
}

void SelectEndState::Update()
{
	m_titleFlow->InputKey();

	//		シーン切り替え処理
	ChangeSceneProcess();
}

void SelectEndState::Finalize()
{
	m_titleFlow->SelectionInfromationReset();
}

void SelectEndState::ChangeSceneProcess()
{
	if (m_titleFlow->SelectionBarMoveProcess())
	{
		if (m_titleFlow->GetSelectionBarMoveDirection() == TitleFlowManager::SelectionBarMoveDirection::Up)
		{
			//		設定選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
		}
		else
		{
			//		開始選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::SettingState);
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
			//		ゲームを終了する
			//PostQuitMessage(0);
			m_titleFlow->GameExitObserver();
		}
	}
}
