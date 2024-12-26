/*
* @file		MenuTabUIObserver.h
* @brief	メニューのTabUIオブザーバー
* @author	Morita
* @date		2024/12/19
*/

#include "pch.h"

#include "MenuTabUIObserver.h"

MenuTabUIObserver::MenuTabUIObserver()
{
}

MenuTabUIObserver::~MenuTabUIObserver()
{
}

void MenuTabUIObserver::AddObserver(IMenuTabUIObserver* observer)
{
	m_observer.push_back(observer);
}

void MenuTabUIObserver::DeleteObserver(IMenuTabUIObserver* observer)
{
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void MenuTabUIObserver::TabMove(float move)
{
	for (const auto& e : m_observer)
	{
		e->TabMove(move);
	}
}

void MenuTabUIObserver::TabUseJudgement(float judgement)
{
	for (const auto& e : m_observer)
	{
		e->TabUseJudgement(judgement);
	}
}

void MenuTabUIObserver::Dalete()
{
	m_observer.clear();
}
