/*
* @file		SelectPlayerState.cpp
* @brief	�v���C��I���������
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
	//		�L�[���͏���
	m_titleSelectManager->InputKey();

	//		UI�̈ړ�����
	UIMove();

	//		�V�[���؂�ւ�����
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
	//		�L�[�������Ȃ������ꍇ���������Ȃ�
	if (!m_titleSelectManager->GetKeyInput()) return;

	//		�o�ߎ�k��
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		��Ɉړ�
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);
	}
	//		���Ɉړ�
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);
	}
}

void SelectPlayState::ChangeSceneProcess()
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
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleSelectManager::State::ChangState);
		}
	}
	else
	{

		//		�ړ������ɂ���ď�Ԃ�؂�ւ���
		if (!m_titleSelectManager->GetDirection())
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleSelectManager::State::EndState);
		}
		else
		{
			//		�ݒ�I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleSelectManager::State::SettingState);
		}
	}
}