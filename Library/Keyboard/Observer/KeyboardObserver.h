/*
* @file		KeyboardObserver.h
* @brief	�L�[�{�[�h�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "IKeyboardObserver.h"

#include "../KeyboardList.h"

class KeyboardObserver
{
public:

	//		�R���X�g���N�^
	KeyboardObserver();

	//		�f�X�g���N�^
	~KeyboardObserver();

	/*
	*	�������u�Ԃ̃I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*	@param	(key)		�L�[����
	*	@param	(keyboard)	�L�[�{�[�h�̏������e
	*/
	void AddPressedObserver(IKeyboardObserver* observer,
					 DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	�������u�Ԃ̃I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*	@param	(key)		�L�[����
	*	@param	(keyboard)	�L�[�{�[�h�̏������e
	*/
	void AddReleasedObserver(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	�L�[�������Ă���I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*	@param	(key)		�L�[����
	*	@param	(keyboard)	�L�[�{�[�h�̏������e
	*/
		void AddStateObserver(IKeyboardObserver* observer,
		DirectX::Keyboard::Keys key, KeyboardList::KeyboardList keyboard);

	/*
	*	�������u�Ԃ̃I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeletePressedObserver(KeyboardList::KeyboardList keyboard);

	/*
	*	�������u�Ԃ̃I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteReleasedObserver(KeyboardList::KeyboardList keyboard);

	/*
	*	�L�[�������Ă���I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteStateObserver(KeyboardList::KeyboardList keyboard);

	//	�L�[�����������̏���
	void IsKeyPressed();

	//	�L�[�𗣂������̏���
	void IsKeyReleased();

	//	�L�[�������Ă��鎞�̏���
	void IsKeyState();

	//		�S�폜
	void Dalete();

private:

	//		�L�[���������u�Ԃ̃I�u�U�[�o�[
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyPressedObserver;

	//		�L�[�𗣂����u�Ԃ̃I�u�U�[�o�[
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyReleasedObserver;

	//		�L�[�������Ă���I�u�U�[�o�[
	std::unordered_map<KeyboardList::KeyboardList, std::pair<IKeyboardObserver*, DirectX::Keyboard::Keys>> m_keyStateObserver;
};