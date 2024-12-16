/*
* @file		TitleUIObserver.cpp
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitleUIObserver.h"

TitleUIObserver::TitleUIObserver()
{
}

TitleUIObserver::~TitleUIObserver()
{
}

void TitleUIObserver::AddObserver(ITitleUIObserver* observer)
{
	//		オブザーバーの追加
	m_observer.push_back(observer);
}

void TitleUIObserver::DeleteObserver(ITitleUIObserver* observer)
{
	//		オブザーバーの削除
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitleUIObserver::DownSelect(float processingTime)
{
	//		下選択処理
	for (const auto& e : m_observer)
	{
		e->DownSelect(processingTime);
	}
}

void TitleUIObserver::UpSelect(float processingTime)
{
	//		上選択処理
	for (const auto& e : m_observer)
	{
		e->UpSelect(processingTime);
	}
}

void TitleUIObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}
