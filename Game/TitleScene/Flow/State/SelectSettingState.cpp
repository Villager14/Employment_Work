/*
* @file		SelectSettingState.cpp
* @brief	設定を選択した状態
* @author	Morita
* @date		2024/05/26
*/

#include "pch.h"

#include "SelectSettingState.h"

#include "../TitleFlowManager.h"

SelectSettingState::SelectSettingState(TitleFlowManager* titleFlowManager)
	:
	m_titleFlow(titleFlowManager)
{
}

SelectSettingState::~SelectSettingState()
{
}

void SelectSettingState::Initialize()
{
	m_titleFlow->AnimationObserver()->SettingAnimation();
}

void SelectSettingState::Update()
{
	m_titleFlow->InputKey();

	//		シーン切り替え処理
	ChangeSceneProcess();

}

void SelectSettingState::Finalize()
{
	m_titleFlow->SelectionInfromationReset();
}

void SelectSettingState::ChangeSceneProcess()
{
	if (m_titleFlow->SelectionBarMoveProcess())
	{
		if (m_titleFlow->GetSelectionBarMoveDirection() == TitleFlowManager::SelectionBarMoveDirection::Up)
		{
			//		開始選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::EndState);
		}
		else
		{
			//		終了選択状態にする
			m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
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
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
			
			//		メニューを開く
			m_titleFlow->MenuUse();
		}
	}
}
