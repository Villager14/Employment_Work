/*
* @file		SelectSettingState.cpp
* @brief	�ݒ��I���������
* @author	Morita
* @date		2024/05/26
*/

#include "pch.h"

#include "SelectSettingState.h"

SelectSettingState::SelectSettingState(TitleSelectManager* titleSelectManager)
	:
	m_titleSelectManager(titleSelectManager),
	m_time(0.0f)
{
}

SelectSettingState::~SelectSettingState()
{
}

void SelectSettingState::Initialize()
{
}

void SelectSettingState::Update()
{
	//		�L�[���͏���
	m_titleSelectManager->InputKey();
	
	//		UI�̈ړ�����
	UIMove();

	//		�V�[���؂�ւ�����
	ChangeSceneProcess();

}

void SelectSettingState::Render()
{
}

void SelectSettingState::Finalize()
{
	m_titleSelectManager->SetKeyInput(false);
	m_time = 0.0f;
}

void SelectSettingState::UIMove()
{
	//		�L�[�������Ȃ������ꍇ���������Ȃ�
	if (!m_titleSelectManager->GetKeyInput()) return;

	//		�o�ߎ���
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * m_titleSelectManager->GetMoveSpeed();

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		��Ɉړ�
	if (m_titleSelectManager->GetDirection())
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);
	}
	//		���Ɉړ�
	else
	{
		m_titleSelectManager->CentreUP(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Play);

		m_titleSelectManager->CenterUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::Setting);

		m_titleSelectManager->UPUnder(m_titleSelectManager->GetDirection(), m_time, TitleSelectManager::TitleUIType::End);
	}
}

void SelectSettingState::ChangeSceneProcess()
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
			//		���j���[���J��
			m_titleSelectManager->GetMenuInformation()->SetMenuJudgement(true);
		}
	}
	else
	{

		if (m_titleSelectManager->GetDirection())
		{
			//		�ݒ�I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleSelectManager::State::EndState);
		}
		else
		{
			//		�I���I����Ԃɂ���
			m_titleSelectManager->ChangeState(TitleSelectManager::State::PlayState);
		}
	}
}
