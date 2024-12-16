#pragma once

#include "pch.h"

class IPSpeedObserver
{
public:

	//		デストラクタ
	~IPSpeedObserver() = default;

	//		ダッシュのクールタイム
	virtual void NowSpeed(float speed) = 0;
};