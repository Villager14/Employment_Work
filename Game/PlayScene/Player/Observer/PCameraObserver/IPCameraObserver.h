#pragma once

#include "pch.h"

class IPCameraObserver
{
public:

	//		�f�X�g���N�^
	~IPCameraObserver() = default;

	//		���h�炷
	virtual void ShakeHead() = 0;

	//		�J�������~�߂�
	virtual void CameraStop() = 0;

	virtual void WallWalkMove(float height) = 0;

	virtual void Direction(DirectX::SimpleMath::Vector3) = 0;

	virtual void WallNormalize(DirectX::SimpleMath::Vector3) = 0;
};