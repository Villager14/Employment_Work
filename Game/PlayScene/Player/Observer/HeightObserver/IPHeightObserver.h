#pragma once

#include "pch.h"

class IPHeightObserver
{
public:

	//		デストラクタ
	~IPHeightObserver() = default;

	//		顔を揺らす
	virtual void PlayerHeght(DirectX::SimpleMath::Vector3 height) = 0;
};