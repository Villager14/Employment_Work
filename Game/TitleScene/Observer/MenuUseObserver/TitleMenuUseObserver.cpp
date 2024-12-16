/*
* @file		TitleUIObserver.cpp
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleMenuUseObserver.h"

TitleMenuUseObserver::TitleMenuUseObserver()
{
}

TitleMenuUseObserver::~TitleMenuUseObserver()
{
}

void TitleMenuUseObserver::AddObserver(ITitleMenuUseObserver* observer)
{
	//		オブザーバーの追加
	m_observer.push_back(observer);
}

void TitleMenuUseObserver::DeleteObserver(ITitleMenuUseObserver* observer)
{
	//		オブザーバーの削除
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitleMenuUseObserver::MenuUse()
{
	//		メニューを開く
	for (const auto& e : m_observer)
	{
		e->OpenMenu();
	}
}

void TitleMenuUseObserver::EnableMenu()
{
	//		メニューを使用できるようにする
	for (const auto& e : m_observer)
	{
		e->EnableMenu();
	}
}

void TitleMenuUseObserver::DisableMenu()
{
	//		メニューを使用出来ないようにする
	for (const auto& e : m_observer)
	{
		e->DisableMenu();
	}
}

void TitleMenuUseObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}
