#pragma once

#include "pch.h"

class IPHeightObserver
{
public:

	//		�f�X�g���N�^
	~IPHeightObserver() = default;

	//		���h�炷
	virtual void PlayerHeght(DirectX::SimpleMath::Vector3 height) = 0;
};