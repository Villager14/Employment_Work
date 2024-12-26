/*
* @file		MenuUsedObserver.cpp
* @brief	メニューを使えるか判断するオブザーバー
* @author	Morita
* @date		2024/12/23
*/

#include "pch.h"

#include "MenuUsedObserver.h"

MenuUsedObserver::MenuUsedObserver()
{
}

MenuUsedObserver::~MenuUsedObserver()
{
}

void MenuUsedObserver::AddObserver(IMenuUsedObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuUsedObserver::DeleteObserver(IMenuUsedObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuUsedObserver::MenuUseJudgement(bool judgement)
{
	for (const auto& e : m_observer)
	{
		e->MenuUseJudgement(judgement);
	}
}

void MenuUsedObserver::Dalete()
{
	m_observer.clear();
}
