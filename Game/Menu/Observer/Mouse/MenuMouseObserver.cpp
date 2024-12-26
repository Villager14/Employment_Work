/*
* @file		MenuMouseObserver.cpp
* @brief	メニューのマウスオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuMouseObserver.h"

MenuMouseObserver::MenuMouseObserver()
{
}

MenuMouseObserver::~MenuMouseObserver()
{
}

void MenuMouseObserver::AddObserver(IMenuMouseObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuMouseObserver::DeleteObserver(IMenuMouseObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuMouseObserver::MousePositionX(int x)
{
	for (const auto& e : m_observer)
	{
		e->MousePositionX(x);
	}
}

void MenuMouseObserver::MousePositionY(int y)
{
	for (const auto& e : m_observer)
	{
		e->MousePositionY(y);
	}
}

void MenuMouseObserver::Dalete()
{
	m_observer.clear();
}
