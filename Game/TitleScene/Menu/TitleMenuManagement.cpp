

#include "pch.h"

#include "TitleMenuManagement.h"

TitleMenuManagement::TitleMenuManagement(MenuInformation* information)
	:
	m_menuInformation(information)
{
}

TitleMenuManagement::~TitleMenuManagement()
{
}

bool TitleMenuManagement::MenuUseJudgement()
{
	//		���j���[���J���Ă���ꍇ
	if (m_menuInformation->GetMenuJudgement()) return true;

	return false;
}

void TitleMenuManagement::OpenMenu()
{
	//		���j���[���g�p����
	m_menuInformation->SetMenuJudgement(true);
}

void TitleMenuManagement::EnableMenu()
{
	//		���j���[���g�p�ł���悤�ɂ���
	m_menuInformation->SetMenuUseJudgement(true);
}

void TitleMenuManagement::DisableMenu()
{
	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	m_menuInformation->SetMenuUseJudgement(false);
}
