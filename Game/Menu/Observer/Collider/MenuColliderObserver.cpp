/*
* @file		MenuColliderObserver.cpp
* @brief	メニューの当たり判定オブザーバー
* @author	Morita
* @date		2024/12/22
*/

#include "pch.h"

#include "MenuColliderObserver.h"

MenuColliderObserver::MenuColliderObserver()
{
}

MenuColliderObserver::~MenuColliderObserver()
{
}

void MenuColliderObserver::AddObserver(IMenuColliderObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuColliderObserver::DeleteObserver(IMenuColliderObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuColliderObserver::HitUIType(UISubType type)
{
	for (const auto& e : m_observer)
	{
		e->HitUIType(type);
	}
}

void MenuColliderObserver::Dalete()
{
	m_observer.clear();
}
