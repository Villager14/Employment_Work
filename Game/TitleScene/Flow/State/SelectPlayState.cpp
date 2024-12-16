/*
* @file		SelectPlayerState.cpp
* @brief	�v���C��I���������
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

	//		�V�[���؂�ւ�����
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
			//		�ݒ�I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::SettingState);
		}
		else
		{
			//		�I���I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::EndState);
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
			//		�I���I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::ChangState);
		}
	}
}
