/*
* @file		ITitleUIObserver.h
* @brief	�^�C�g��UI�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class ITitleUIObserver
{
public:

	//		�f�X�g���N�^
	~ITitleUIObserver() = default;

	/*
	*	����I������
	* 
	*	@param	(processingTime)	��������
	*/
	virtual void DownSelect(float processingTime) = 0;

	/*
	*	���I������
	*
	*	@param	(processingTime)	��������
	*/
	virtual void UpSelect(float processingTime) = 0;
};