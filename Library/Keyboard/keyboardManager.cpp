/*
* @file		KeyboardManager.h
* @brief	�L�[�{�[�h�}�l�[�W���[
* @author	Morita
* @date		2024/12/21
*/

#include "pch.h"

#include "KeyboardManager.h"

KeyboardManager::KeyboardManager()
{
	//		�L�[�{�[�h�I�u�U�[�o�[���쐬����
	m_keyboardObserver = std::make_unique<KeyboardObserver>();
}

KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	//		�L�[�̉������u�Ԃ̏���
	m_keyboardObserver->IsKeyPressed();

	//		�L�[�̊J�������u�Ԃ̏���
	m_keyboardObserver->IsKeyReleased();

	//		�L�[�̉����Ă���Ƃ��̏���
	m_keyboardObserver->IsKeyState();
}

void KeyboardManager::Finalize()
{
	//		�O�I�u�U�[�o�[�̍폜
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
