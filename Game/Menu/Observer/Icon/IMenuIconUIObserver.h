/*
* @file		IMenuIconUIObserver.h
* @brief	���j���[�̃A�C�R���I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/20
*/
#pragma once

#include "pch.h"

class IMenuIconUIObserver
{
public:

	//		�f�X�g���N�^
	~IMenuIconUIObserver() = default;

	/*
	*	�A�C�R���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	virtual void IconMoveProcess(float move) = 0;

};