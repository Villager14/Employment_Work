/*
* @file		IKeyboardObserver.h
* @brief	�L�[�{�[�h�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "pch.h"

#include "../KeyboardList.h"

class IKeyboardObserver
{
public:

	//		�f�X�g���N�^
	~IKeyboardObserver() = default;

	/*
	*	�L�[�{�[�h�̉������u�Ԃ̏���
	* 
	*	@param	(key)	�������L�[
	*/
	virtual void IsKeyPressed(KeyboardList::KeyboardList key) = 0;

	/*
	*	�L�[�{�[�h�̗������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	virtual void IsKeyReleased(KeyboardList::KeyboardList key) = 0;

	/*
	*	�L�[�{�[�h�̉����Ă��鎞�̏���
	*
	*	@param	(key)	�������L�[
	*/
	virtual void IsKeyState(KeyboardList::KeyboardList key) = 0;

};