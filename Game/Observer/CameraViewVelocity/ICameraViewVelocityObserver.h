/*
* @file		ICameraViewVelocityObserver.h
* @brief	�J�����̃r���[�x�N�g���I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/16
*/
#pragma once

#include "pch.h"

class ICameraViewVelocityObserver
{
public:

	//		�f�X�g���N�^
	~ICameraViewVelocityObserver() = default;

	//		�J�����̃r���[�x�N�g��
	virtual void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity) = 0;

	//		�J�����̃r���[
	virtual void CameraView(DirectX::SimpleMath::Vector3 view) = 0;

	//		�J�����̃A�b�v
	virtual void CameraUp(DirectX::SimpleMath::Vector3 up) = 0;
};