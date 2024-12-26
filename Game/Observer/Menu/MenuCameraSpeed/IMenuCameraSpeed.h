/*
* @file		IMenuCameraSpeed.h
* @brief	���j���[�̃J�����̑��x���󂯎��I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuCameraSpeed
{
public:

	//		�f�X�g���N�^
	~IMenuCameraSpeed() = default;

	//		���j���[�̃J�����̑��x
	virtual void GetMenuCameraSpeed(float speed) = 0;
};