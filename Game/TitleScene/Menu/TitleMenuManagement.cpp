

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
	//		���j���[���J���Ă���ꍇ
	if (m_menuUseJudgement) return true;

	return false;
}

void TitleMenuManagement::OpenMenu()
{
	//		���j���[���g�p����
	m_menuOpenObserver->MenuOpen();
}

void TitleMenuManagement::EnableMenu()
{
	//		���j���[���g�p�ł���悤�ɂ���
	m_menuUsedObserver->MenuUseJudgement(true);
}

void TitleMenuManagement::DisableMenu()
{
	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	m_menuUsedObserver->MenuUseJudgement(false);
}
