/*
* @file		EasingFunction.h
* @brief	�C�[�W���O�֐�
* @author	Morita
* @date		2024/11/28
*/

#pragma once

//#include "pch.h"

namespace EasingProcess
{
	
	//https://easings.net/ja#easeOutQuart
	inline float EaseOutQuart(float val)
	{
		return 1.0f - pow(1.0f - val, 4.0f);
	}
}