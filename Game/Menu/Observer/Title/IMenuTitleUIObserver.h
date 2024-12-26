/*
* @file		IMenuTitleUIObserver.h
* @brief	���j���[�^�C�g��UI�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

class IMenuTitleUIObserver
{
public:

	//		�f�X�g���N�^
	~IMenuTitleUIObserver() = default;

	/*
	*	�^�C�g���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	virtual void TitleMoveProcess(float move) = 0;

};