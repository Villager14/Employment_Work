/*
* @file		SelectEndState.cpp
* @brief	�I����I���������
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

	//		�V�[���؂�ւ�����
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
			//		�ݒ�I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::PlayState);
		}
		else
		{
			//		�J�n�I����Ԃɂ���
			m_titleFlow->ChangeState(TitleFlowManager::State::SettingState);
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
			//		�Q�[�����I������
			//PostQuitMessage(0);
			m_titleFlow->GameExitObserver();
		}
	}
}
