#pragma once

#include "pch.h"

class IPObserver
{
public:

	//		�f�X�g���N�^
	~IPObserver() = default;

	//		�_�b�V���̃N�[���^�C��
	virtual void DashCoolTime(float coolTime) = 0;
};