/*
* @file		TitlePostEffectObserver.cpp
* @brief	ポストエフェクトオブザーバー
* @author	Morita
* @date		2024/12/12
*/

#include "pch.h"

#include "TitlePostEffectObserver.h"

TitlePostEffectObserver::TitlePostEffectObserver()
{
}

TitlePostEffectObserver::~TitlePostEffectObserver()
{
}

void TitlePostEffectObserver::AddObserver(ITitlePostEffectObserver* observer)
{
	//		オブザーバーを追加する
	m_observer.push_back(observer);
}

void TitlePostEffectObserver::DeleteObserver(ITitlePostEffectObserver* observer)
{
	//		オブザーバーを削除する
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitlePostEffectObserver::FadeIn()
{
	//		フェードインの処理
	for (const auto& e : m_observer)
	{
		e->FadeIn();
	}
}

void TitlePostEffectObserver::FadeOut()
{
	//		フェードアウトの処理
	for (const auto& e : m_observer)
	{
		e->FadeOut();
	}
}

void TitlePostEffectObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}
