/*
* @file		KeyboardObserver.h
* @brief	キーボードオブザーバー
* @author	Morita
* @date		2024/12/21
*/

#include "pch.h"

#include "KeyboardObserver.h"

KeyboardObserver::KeyboardObserver()
{
}

KeyboardObserver::~KeyboardObserver()
{
}

void KeyboardObserver::AddPressedObserver(IKeyboardObserver* observer,
									DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの追加
	m_keyPressedObserver[keyboard] = { observer, key };
}

void KeyboardObserver::AddReleasedObserver(IKeyboardObserver* observer, DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの追加
	m_keyReleasedObserver[keyboard] = { observer, key };
}

void KeyboardObserver::AddStateObserver(IKeyboardObserver* observer, DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの追加
	m_keyStateObserver[keyboard] = { observer, key };
}

void KeyboardObserver::DeletePressedObserver(KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの削除
	m_keyPressedObserver.erase(keyboard);
}

void KeyboardObserver::DeleteReleasedObserver(KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの削除
	m_keyReleasedObserver.erase(keyboard);
}

void KeyboardObserver::DeleteStateObserver(KeyboardList::KeyboardList keyboard)
{
	//		オブザーバーの削除
	m_keyStateObserver.erase(keyboard);
}

void KeyboardObserver::IsKeyPressed()
{
	for (const auto& e : m_keyPressedObserver)
	{
		if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->IsKeyPressed(e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void KeyboardObserver::IsKeyReleased()
{
	for (const auto& e : m_keyReleasedObserver)
	{
		if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->IsKeyPressed(e.second.second))
		{
			e.second.first->IsKeyReleased(e.first);
		}
	}
}

void KeyboardObserver::IsKeyState()
{
	for (const auto& e : m_keyStateObserver)
	{
		if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->IsKeyPressed(e.second.second))
		{
			e.second.first->IsKeyState(e.first);
		}
	}
}

void KeyboardObserver::Dalete()
{
	//		全てを削除する
	m_keyPressedObserver.clear();
	m_keyReleasedObserver.clear();
	m_keyStateObserver.clear();
}
