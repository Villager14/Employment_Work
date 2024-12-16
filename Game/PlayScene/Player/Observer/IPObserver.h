#pragma once

#include "pch.h"

class IPObserver
{
public:

	//		デストラクタ
	~IPObserver() = default;

	//		ダッシュのクールタイム
	virtual void DashCoolTime(float coolTime) = 0;
};