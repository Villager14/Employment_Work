
#pragma once

#include "pch.h"

struct OInformation
{
	//		座標
	DirectX::SimpleMath::Vector3 position;

	//		角度
	DirectX::SimpleMath::Quaternion quaternion;

	//		高さ
	float length = 0;
};