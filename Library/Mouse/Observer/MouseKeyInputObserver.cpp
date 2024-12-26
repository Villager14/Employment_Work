/*
* @file		MouseKeyInputObserver.cpp
* @brief	マウスのキー入力オブザーバー
* @author	Morita
* @date		2024/12/22
*/

#include "pch.h"

#include "MouseKeyInputObserver.h"

MouseKeyInputObserver::MouseKeyInputObserver()
{
	//		マウスの入力処理の生成
	m_keyInputProcess = std::make_unique<MouseKeyInputProcess>();
}

MouseKeyInputObserver::~MouseKeyInputObserver()
{
}

void MouseKeyInputObserver::AddPressedObserver(IMouseKeyInputObserver* observer,
												KeyInputMouse::MouseState state,
												KeyInputMouse::MouseList key)
{
	//		オブザーバーを追加
	m_pressedObserver[key] = { observer, state };
}

void MouseKeyInputObserver::AddReleasedObserver(IMouseKeyInputObserver* observer,
												KeyInputMouse::MouseState state,
												KeyInputMouse::MouseList key)
{
	//		オブザーバーを追加
	m_releasedObserver[key] = { observer, state };
}

void MouseKeyInputObserver::AddKeepPushingObserver(IMouseKeyInputObserver* observer,
													KeyInputMouse::MouseState state,
													KeyInputMouse::MouseList key)
{
	//		オブザーバーを追加
	m_keepPushingObserver[key] = { observer, state };
}

void MouseKeyInputObserver::DeletePressedObserver(KeyInputMouse::MouseList keyboard)
{
	//		キーがある場合処理を行う
	if (m_pressedObserver.find(keyboard) != m_pressedObserver.end())
	{
		//		オブザーバーの削除
		m_pressedObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::DeleteReleasedObserver(KeyInputMouse::MouseList keyboard)
{
	//		キーがある場合処理を行う
	if (m_releasedObserver.find(keyboard) != m_releasedObserver.end())
	{

		//		オブザーバーの削除
		m_releasedObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::DeleteKeepPushingObserver(KeyInputMouse::MouseList keyboard)
{
	//		キーがある場合処理を行う
	if (m_keepPushingObserver.find(keyboard) != m_keepPushingObserver.end())
	{

		//		オブザーバーの削除
		m_keepPushingObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::IsKeyPressed()
{
	for (const auto& e : m_pressedObserver)
	{
		//		キーを押した場合
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().PRESSED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::IsKeyReleased()
{
	for (const auto& e : m_releasedObserver)
	{
		//		キーを押した場合
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().RELEASED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::IsKeepPushing()
{
	for (const auto& e : m_keepPushingObserver)
	{
		//		キーを押した場合
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().RELEASED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::Dalete()
{
	//		全てを削除する
	m_pressedObserver.clear();
	m_releasedObserver.clear();
	m_keepPushingObserver.clear();
}