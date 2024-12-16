

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
	//		メニューを開いている場合
	if (m_menuInformation->GetMenuJudgement()) return true;

	return false;
}

void TitleMenuManagement::OpenMenu()
{
	//		メニューを使用する
	m_menuInformation->SetMenuJudgement(true);
}

void TitleMenuManagement::EnableMenu()
{
	//		メニューを使用できるようにする
	m_menuInformation->SetMenuUseJudgement(true);
}

void TitleMenuManagement::DisableMenu()
{
	//		メニューを使用できないようにする
	m_menuInformation->SetMenuUseJudgement(false);
}
