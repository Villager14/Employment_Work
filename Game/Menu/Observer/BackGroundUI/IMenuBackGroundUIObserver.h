/*
* @file		IMenuBackGroundUIObserver.h
* @brief	���j���[�̔w�iUI�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

class IMenuBackGroundUIObserver
{
public:

	//		�f�X�g���N�^
	~IMenuBackGroundUIObserver() = default;

	/*
	*	�o�[�̃X�P�[���̕ύX
	*
	*	@param	(float scale)
	*/
	virtual void BackGroundBarScale(float scale) = 0;

	/*
	*	���j���[�̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	virtual void MenuMoveProcess(float move) = 0;

};