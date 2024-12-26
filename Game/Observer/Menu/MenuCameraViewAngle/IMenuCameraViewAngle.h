/*
* @file		IMenuCameraViewAngle.h
* @brief	���j���[�̃J�����̎���p�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuCameraViewAngle
{
public:

	//		�f�X�g���N�^
	~IMenuCameraViewAngle() = default;

	//		���j���[�̃J�����̎���p
	virtual void GetMenuCameraViewAngle(float angle) = 0;
};