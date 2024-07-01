/*
* @file		SelectEndState.cpp
* @brief	�I����I���������
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
	//		�L�[���͏���
	m_titleSelectManager->InputKey();

	UIMove();

	//		UI�̈ړ�����
	//UIMove();

	//		�V�[���؂�ւ�����
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
	//		�L�[�������Ȃ������ꍇ���������Ȃ�
	if (!m_titleSelectManager->GetKeyInput()) return;

	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		��Ɉړ�
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);
	}
	//		���Ɉړ�
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Setting);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::End);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::UIType::Play);
	}
}

void SelectEndState::ChangeSceneProcess()
{
	//		���Ԃ��P�ȉ��̏ꍇ���������Ȃ�
	if (m_time < 1.0f)
	{
		//		�L�[�{�[�h�̎擾
		DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

		//		�{�^���̎擾
		DirectX::Mouse::ButtonStateTracker button = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

		if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
			button.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
		{
			PostQuitMessage(0);
		}
	}
	else
	{
		if (m_titleSelectManager->GetDirection())
		{
			//		�ݒ�I����Ԃɂ���
			m_titleSelectManager->ChangeState(m_titleSelectManager->GetSelectPlayState());
		}
		else
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(m_titleSelectManager->GetSelectSettingState());
		}
	}

}
