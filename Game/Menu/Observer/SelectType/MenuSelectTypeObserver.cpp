/*
* @file		MenuSelectTypeObserver.cpp
* @brief	メニューの選択オブザーバー
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuSelectTypeObserver.h"

MenuSelectTypeObserver::MenuSelectTypeObserver()
{
}

MenuSelectTypeObserver::~MenuSelectTypeObserver()
{
}

void MenuSelectTypeObserver::AddObserver(IMenuSelectTypeObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuSelectTypeObserver::DeleteObserver(IMenuSelectTypeObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuSelectTypeObserver::SelectType(MenuUITaype::UIType type)
{
	for (const auto& e : m_observer)
	{
		e->SelectType(type);
	}
}

void MenuSelectTypeObserver::Dalete()
{
	m_observer.clear();
}
