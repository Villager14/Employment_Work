/*
* @file		MenuOpenJudgementObserver.cpp
* @brief	メニュー開いているか判断するオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuOpenJudgementObserver.h"

MenuOpenJudgementObserver::MenuOpenJudgementObserver()
{
}

MenuOpenJudgementObserver::~MenuOpenJudgementObserver()
{
}

void MenuOpenJudgementObserver::AddObserver(IMenuOpenJudgementObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuOpenJudgementObserver::DeleteObserver(IMenuOpenJudgementObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuOpenJudgementObserver::MenuOpen()
{
	for (const auto& e : m_observer)
	{
		e->MenuOpen();
	}
}

void MenuOpenJudgementObserver::MenuClose()
{
	for (const auto& e : m_observer)
	{
		e->MenuClose();
	}
}

void MenuOpenJudgementObserver::Dalete()
{
	m_observer.clear();
}
