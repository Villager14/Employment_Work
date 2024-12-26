/*
* @file		MenuClose.cpp
* @brief	���j���[����鎞�̏���
* @author	Morita
* @date		2024/07/11
*/

#include "pch.h"

#include "MenuClose.h"

MenuClose::MenuClose(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow),
	m_scale(0.0f),
	m_move(0.0f),
	m_mainClose(0.0f)
{
}

MenuClose::~MenuClose()
{
}

void MenuClose::Initialize()
{
	m_move = 0.0f;
	m_scale = 0.0f;
	m_mainClose = 1.0f;

	//		�I�[�f�B�I��I������
	m_menuFlow->GetSelectTypeObserver()->SelectType(MenuUITaype::Close);

	//		TabUI���g�p�o���Ȃ��悤�ɂ���
	m_menuFlow->GetMenuTabUIObserver()->TabUseJudgement(false);
}

void MenuClose::Update()
{
	if (m_move < 1.0f)
	{
		m_move += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

		m_move = Library::Clamp(m_move, 0.0f, 1.0f);

		float transrationTime = m_menuFlow->EasingBackUI(m_move);

		//		�w�i�̈ړ�����
		m_menuFlow->GetMenuBackGroundUIObserver()->MenuMoveProcess(1.0f - transrationTime);

		/*
		//		�o�[�P�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar1].position =
		{ 0.0f, Library::Lerp(300.0f, 13.0f, transrationTime) };

		//		�o�[�Q�̈ړ�
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::Bar2].position =
		{ 0.0f, Library::Lerp(-300.0f, -13.0f, transrationTime) };

		//		�w�i�̃X�P�[���k��
		(*m_menuManager->GetInformation()->GetStandardShader()
			->GetUIInformation())[MenuInformation::UIType::BackGround].scale =
		{ 1.0f, 1 - transrationTime };
		*/
	}
	else
	{
		m_scale += LibrarySingleton::GetInstance()->GetElpsedTime() * MENU_SPEED;

			m_scale = Library::Clamp(m_scale, 0.0f, 1.0f);

			float transrationTime = m_menuFlow->EasingBackUI(m_scale);

			//		�w�i�̃o�[�̃X�P�[���̕ύX
			m_menuFlow->GetMenuBackGroundUIObserver()->BarScale(1.0f - transrationTime);

			/*
			//		�o�[�P�̃X�P�[���k��
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar1].scale =
			{ 1.0f - transrationTime, 1.0f };

			//		�o�[�Q�̃X�P�[���k��
			(*m_menuManager->GetInformation()->GetStandardShader()
				->GetUIInformation())[MenuInformation::UIType::Bar2].scale =
			{ 1.0f - transrationTime, 1.0f };
		*/
	}

	if (m_scale >= 1.0f)
	{
		m_menuFlow->ChangState(MenuFlow::Standby);
	}
	
}

void MenuClose::Render()
{
}

void MenuClose::Finalize()
{
	//		���j���[���I������
	m_menuFlow->SetMenuEndJudgement(true);
}
