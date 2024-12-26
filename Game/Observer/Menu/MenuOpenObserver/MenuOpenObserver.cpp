/*
* @file		MenuOpenObserver.cpp
* @brief	メニュー開くオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuOpenObserver.h"

MenuOpenObserver::MenuOpenObserver()
{
}

MenuOpenObserver::~MenuOpenObserver()
{
}

void MenuOpenObserver::AddObserver(IMenuOpenObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuOpenObserver::DeleteObserver(IMenuOpenObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuOpenObserver::MenuOpen()
{
	for (const auto& e : m_observer)
	{
		e->MenuOpen();
	}
}

void MenuOpenObserver::Dalete()
{
	m_observer.clear();
}
