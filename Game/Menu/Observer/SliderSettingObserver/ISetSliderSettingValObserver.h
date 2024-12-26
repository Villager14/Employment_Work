/*
* @file		ISetSliderSettignValObserver.h
* @brief	�X���C�_�[�̒l��ݒ�ɑ���I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/26
*/

#pragma once

#include "pch.h"

class ISetSliderSettingValObserver
{
public:

	//		�f�X�g���N�^
	~ISetSliderSettingValObserver() = default;

	/*
	*	����p�̒l���󂯎��
	* 
	*	@param	(val)�@����̊���
	*/
	virtual void SetFov(float val) = 0;

	/*
	*	�}�E�X���x���󂯎��
	*
	*	@param	(val)�@���x�̊���
	*/
	virtual void SetMouseSensitivity(float val) = 0;
};