/*
* @file		MenuTitleUIObserver.cpp
* @brief	メニューのタイトルUIオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuTitleUIObserver.h"

MenuTitleUIObserver::MenuTitleUIObserver()
{
}

MenuTitleUIObserver::~MenuTitleUIObserver()
{
}

void MenuTitleUIObserver::AddObserver(IMenuTitleUIObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuTitleUIObserver::DeleteObserver(IMenuTitleUIObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuTitleUIObserver::TitleMoveProcess(float move)
{
	for (const auto& e : m_observer)
	{
		e->TitleMoveProcess(move);
	}
}

void MenuTitleUIObserver::Dalete()
{
	m_observer.clear();
}
