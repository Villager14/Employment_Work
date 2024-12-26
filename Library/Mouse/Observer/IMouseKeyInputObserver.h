/*
* @file		IMouseKeyInputObserver.h
* @brief	�}�E�X�̃L�[���̓I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "pch.h"

#include "../MouseList.h"

class IMouseKeyInputObserver
{
public:

	//		�f�X�g���N�^
	~IMouseKeyInputObserver() = default;

	/*
	*	�}�E�X�̉������u�Ԃ̏���
	* 
	*	@param	(key)	�������L�[
	*/
	virtual void IsKeyPressed(KeyInputMouse::MouseList key) = 0;

	/*
	*	�}�E�X�̗������u�Ԃ̏���
	*
	*	@param	(key)	�������L�[
	*/
	virtual void IsKeyReleased(KeyInputMouse::MouseList key) = 0;

	/*
	*	�}�E�X�̉����������̎��̏���
	*
	*	@param	(key)	�����������L�[
	*/
	virtual void IsKeepPushing(KeyInputMouse::MouseList key) = 0;
};