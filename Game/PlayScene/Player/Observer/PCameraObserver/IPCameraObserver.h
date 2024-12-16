#pragma once

#include "pch.h"

class IPCameraObserver
{
public:

	//		デストラクタ
	~IPCameraObserver() = default;

	//		顔を揺らす
	virtual void ShakeHead() = 0;

	//		カメラを止める
	virtual void CameraStop() = 0;

	virtual void WallWalkMove(float height) = 0;

	virtual void Direction(DirectX::SimpleMath::Vector3) = 0;

	virtual void WallNormalize(DirectX::SimpleMath::Vector3) = 0;
};