/*
* @file		SelectSettingState.cpp
* @brief	�ݒ��I���������
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

	//		�V�[���؂�ւ�����
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
			//		�J�n�I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::EndState);
		}
		else
		{
			//		�I���I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
		}

		return;
	}

	if (m_titleFlow->GetSelectionBarMoveDirection() == TitleFlowManager::SelectionBarMoveDirection::Not)
	{
		//		�L�[�{�[�h�̎擾
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		�{�^���̎擾
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			MusicLibrary::GetInstance()->PlaySoundEffect(MusicLibrary::SoundEffectType::Decision);
			
			//		���j���[���J��
			m_titleFlow->MenuUse();
		}
	}
}
