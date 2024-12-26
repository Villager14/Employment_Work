/*
* @file		KeyboardManager.h
* @brief	�L�[�{�[�h�}�l�[�W���[
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "Observer/KeyboardObserver.h"

class KeyboardManager
{
public:

	KeyboardManager();

	~KeyboardManager();

	void Update();

	void Finalize();

public:

	enum KeyType
	{
		Pressed,
		Released,
		State,
	};

public:

	/*
	*	�L�[�{�[�h�̓��͏�����ǉ�����
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃|�C���^�̃C���X�^���X
	*	@param	(key)		�L�[����
	*	@param	(keyboard)	�L�[�{�[�h�̏���
	*	@param	(type)		�L�[�̎��
	*/
	void AddKeyboard(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard, KeyType type);

	/*
	*	�L�[�{�[�h�̓��͏����̍폜
	* 
	*	@param	(keyboard)	�L�[�{�[�h�̏���
	*	@param	(type)		�L�[�̎��
	*/
	void DeleteKeyboard(KeyboardList::KeyboardList keyboard, KeyType type);

private:

	//		�L�[�{�[�h�I�u�U�[�o�[
	std::unique_ptr<KeyboardObserver> m_keyboardObserver;

};