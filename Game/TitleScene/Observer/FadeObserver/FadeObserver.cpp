/*
* @file		FadeObserver.cpp
* @brief	タイトルUIオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "FadeObserver.h"

FadeObserver::FadeObserver()
{
}

FadeObserver::~FadeObserver()
{
}

void FadeObserver::AddObserver(IFadeObserver* observer)
{
	//		オブザーバーの追加
	m_observer.push_back(observer);
}

void FadeObserver::DeleteObserver(IFadeObserver* observer)
{
	//		オブザーバーの削除
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void FadeObserver::SceneEndFadeOut()
{
	//		シーン変更フェードアウト
	for (const auto& e : m_observer)
	{
		e->SceneEndFadeOut();
	}
}

void FadeObserver::FadeOut()
{
	//		フェードアウト
	for (const auto& e : m_observer)
	{
		e->FadeOut();
	}
}

void FadeObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}
