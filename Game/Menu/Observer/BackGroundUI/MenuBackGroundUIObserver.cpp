/*
* @file		MenuBackGroundUIObserver.h
* @brief	メニューの背景UIオブザーバー
* @author	Morita
* @date		2024/12/19
*/
#include "pch.h"

#include "MenuBackGroundUIObserver.h"

MenuBackGroundUIObserver::MenuBackGroundUIObserver()
{
}

MenuBackGroundUIObserver::~MenuBackGroundUIObserver()
{
}

void MenuBackGroundUIObserver::AddObserver(IMenuBackGroundUIObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuBackGroundUIObserver::DeleteObserver(IMenuBackGroundUIObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuBackGroundUIObserver::BarScale(float scale)
{
	for (const auto& e : m_observer)
	{
		e->BackGroundBarScale(scale);
	}
}

void MenuBackGroundUIObserver::MenuMoveProcess(float move)
{
	for (const auto& e : m_observer)
	{
		e->MenuMoveProcess(move);
	}
}

void MenuBackGroundUIObserver::Dalete()
{
	m_observer.clear();
}
