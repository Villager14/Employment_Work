/*
* @file		IMenuCameraViewAngle.h
* @brief	メニューのカメラの視野角オブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuCameraViewAngle
{
public:

	//		デストラクタ
	~IMenuCameraViewAngle() = default;

	//		メニューのカメラの視野角
	virtual void GetMenuCameraViewAngle(float angle) = 0;
};