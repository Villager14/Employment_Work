/*
* @file		IMenuMouseObserver.h
* @brief	���j���[�}�E�X�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "pch.h"

class IMenuMouseObserver
{
public:

	//		�f�X�g���N�^
	~IMenuMouseObserver() = default;

	/*
	*	�}�E�X��X���W�̍X�V
	* 
	*	@param	(x) x���W
	*/
	virtual void MousePositionX(int x) = 0;

	/*
	*	�}�E�X��Y���W�̍X�V
	* 
	*	@param	(y) y���W
	*/
	virtual void MousePositionY(int y) = 0;
};