

#include "pch.h"

#include "TitleMenuManagement.h"

TitleMenuManagement::TitleMenuManagement(MenuUsedObserver* observer,
										 MenuOpenObserver* menuOpenObserver)
	:
	m_menuUseJudgement(false),
	m_menuUsedObserver(observer)
{
}

TitleMenuManagement::~TitleMenuManagement()
{
}

bool TitleMenuManagement::MenuUseJudgement()
{
	//		メニューを開いている場合
	if (m_menuUseJudgement) return true;

	return false;
}

void TitleMenuManagement::OpenMenu()
{
	//		メニューを使用する
	m_menuOpenObserver->MenuOpen();
}

void TitleMenuManagement::EnableMenu()
{
	//		メニューを使用できるようにする
	m_menuUsedObserver->MenuUseJudgement(true);
}

void TitleMenuManagement::DisableMenu()
{
	//		メニューを使用できないようにする
	m_menuUsedObserver->MenuUseJudgement(false);
}
