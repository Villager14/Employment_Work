#pragma once

#include "pch.h"

class IPSpeedObserver
{
public:

	//		�f�X�g���N�^
	~IPSpeedObserver() = default;

	//		�_�b�V���̃N�[���^�C��
	virtual void NowSpeed(float speed) = 0;
};