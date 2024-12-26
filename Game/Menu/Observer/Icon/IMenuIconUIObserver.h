/*
* @file		IMenuIconUIObserver.h
* @brief	メニューのアイコンオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/20
*/
#pragma once

#include "pch.h"

class IMenuIconUIObserver
{
public:

	//		デストラクタ
	~IMenuIconUIObserver() = default;

	/*
	*	アイコンの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	virtual void IconMoveProcess(float move) = 0;

};