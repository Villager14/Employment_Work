/*
* @file		TitlePlayerAnimationObserver.cpp
* @brief	プレイヤーのアニメションオブザーバー
* @author	Morita
* @date		2024/12/16
*/

#include "pch.h"

#include "TitlePlayerAnimationObserver.h"

TitlePlayerAnimationObserver::TitlePlayerAnimationObserver()
{
}

TitlePlayerAnimationObserver::~TitlePlayerAnimationObserver()
{
}

void TitlePlayerAnimationObserver::AddObserver(ITitlePlayerAnimationObserver* observer)
{
	//		オブザーバーを追加する
	m_observer.push_back(observer);
}

void TitlePlayerAnimationObserver::DeleteObserver(ITitlePlayerAnimationObserver* observer)
{
	//		オブザーバーを削除する
	m_observer.erase(std::remove(m_observer.begin(), m_observer.end(), observer), m_observer.end());
}

void TitlePlayerAnimationObserver::Dalete()
{
	//		全てを削除する
	m_observer.clear();
}

void TitlePlayerAnimationObserver::PlayAnimation()
{
	//		プレイアニメーション
	for (const auto& e : m_observer)
	{
		e->PlayAnimation();
	}
}

void TitlePlayerAnimationObserver::SettingAnimation()
{
	//		設定アニメーション
	for (const auto& e : m_observer)
	{
		e->SettingAnimation();
	}
}

void TitlePlayerAnimationObserver::ExitAnimation()
{
	//		終了アニメーション
	for (const auto& e : m_observer)
	{
		e->ExitAnimation();
	}
}
