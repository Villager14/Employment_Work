/*
* @file		IMenuCameraSpeed.h
* @brief	メニューのカメラの速度を受け取るオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuCameraSpeed
{
public:

	//		デストラクタ
	~IMenuCameraSpeed() = default;

	//		メニューのカメラの速度
	virtual void GetMenuCameraSpeed(float speed) = 0;
};