/*
* @file		TitleGameExitObserver.h
* @brief	タイトルゲーム終了オブザーバー
* @author	Morita
* @date		2024/12/13
*/

#include "pch.h"

#include "TitleGameExitObserver.h"

TitleGameExitObserver::TitleGameExitObserver()
{
}

TitleGameExitObserver::~TitleGameExitObserver()
{
}

void TitleGameExitObserver::AddObserver(ITitleGameExitObserver* observer)
{
	//		オブザーバーの追加
	m_observer.push_back(observer);
}

void TitleGameExitObserver::DeleteObserver(ITitleGameExitObserver* observer)
{
	//		オブザーバーの削除
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}


void TitleGameExitObserver::GameExit()
{
	//		ゲーム終了
	for (const auto& e : m_observer)
	{
		e->GameExit();
	}
}

void TitleGameExitObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}
