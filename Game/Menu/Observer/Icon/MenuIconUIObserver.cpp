/*
* @file		MenuIconUIObserver.cpp
* @brief	メニューのアイコンUIオブザーバー
* @author	Morita
* @date		2024/12/20
*/

#include "pch.h"

#include "MenuIconUIObserver.h"

MenuIconUIObserver::MenuIconUIObserver()
{
}

MenuIconUIObserver::~MenuIconUIObserver()
{
}

void MenuIconUIObserver::AddObserver(IMenuIconUIObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuIconUIObserver::DeleteObserver(IMenuIconUIObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuIconUIObserver::IconMoveProcess(float move)
{
	for (const auto& e : m_observer)
	{
		e->IconMoveProcess(move);
	}
}

void MenuIconUIObserver::Dalete()
{
	m_observer.clear();
}
