/*
* @file		MenuStandby.cpp
* @brief	���j���[�ҋ@��Ԃ̏���
* @author	Morita
* @date		2024/12/24
*/

#include "pch.h"

#include "MenuStandby.h"

#include "../MenuFlowCommonProcess.h"

MenuStandby::MenuStandby(MenuFlow* menuFlow)
	:
	m_menuFlow(menuFlow)
{
}

MenuStandby::~MenuStandby()
{
}

void MenuStandby::Initialize()
{
}

void MenuStandby::Update()
{
	//		���j���[���J�n���邩
	if (m_menuFlow->GetMenuOpenKeyJudgement())
	{
		//		���j���[���J�n����
		m_menuFlow->ChangState(MenuFlow::MenuType::Start);
	}
}

void MenuStandby::Render()
{
}

void MenuStandby::Finalize()
{
	//		�J�[�\��������
	ShowCursor(FALSE);

	//		���j���[���J�n����
	m_menuFlow->SetMenuStartJudgement(true);

	//		���j���[�̊J�n�L�[�������Ă��Ȃ���Ԃɂ���
	m_menuFlow->SetMenuOpenKeyJudgement(false);
}
