/*
* @file		ICameraViewVelocityObserver.h
* @brief	カメラのビューベクトルオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/16
*/
#pragma once

#include "pch.h"

class ICameraViewVelocityObserver
{
public:

	//		デストラクタ
	~ICameraViewVelocityObserver() = default;

	//		カメラのビューベクトル
	virtual void CameraViewVelocity(DirectX::SimpleMath::Vector3 velocity) = 0;

	//		カメラのビュー
	virtual void CameraView(DirectX::SimpleMath::Vector3 view) = 0;

	//		カメラのアップ
	virtual void CameraUp(DirectX::SimpleMath::Vector3 up) = 0;
};