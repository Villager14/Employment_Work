/*
* @file		KeyboardManager.h
* @brief	キーボードマネージャー
* @author	Morita
* @date		2024/12/21
*/

#include "pch.h"

#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
{
	//		キーボードオブザーバーを作成する
	m_keyboardObserver = std::make_unique<KeyboardObserver>();
}

KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	//		キーの押した瞬間の処理
	m_keyboardObserver->IsKeyPressed();

	//		キーの開放した瞬間の処理
	m_keyboardObserver->IsKeyReleased();

	//		キーの押しているときの処理
	m_keyboardObserver->IsKeyState();
}

void KeyboardManager::Finalize()
{
	//		前オブザーバーの削除
	m_keyboardObserver->Dalete();
}

void KeyboardManager::AddKeyboard(IKeyboardObserver* observer, DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard, KeyType type)
{
	switch (type)
	{
	case KeyboardManager::Pressed:
		m_keyboardObserver->AddPressedObserver(observer, key, keyboard);
		break;
	case KeyboardManager::Released:
		m_keyboardObserver->AddReleasedObserver(observer, key, keyboard);
		break;
	case KeyboardManager::State:
		m_keyboardObserver->AddStateObserver(observer, key, keyboard);
		break;
	default:
		break;
	}
}

void KeyboardManager::DeleteKeyboard(KeyboardList::KeyboardList keyboard, KeyType type)
{
	switch (type)
	{
	case KeyboardManager::Pressed:
		m_keyboardObserver->DeletePressedObserver(keyboard);
		break;
	case KeyboardManager::Released:
		m_keyboardObserver->DeleteReleasedObserver(keyboard);
		break;
	case KeyboardManager::State:
		m_keyboardObserver->DeleteStateObserver(keyboard);
		break;
	default:
		break;
	}

}
