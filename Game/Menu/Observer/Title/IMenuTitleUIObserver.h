/*
* @file		IMenuTitleUIObserver.h
* @brief	メニュータイトルUIオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

class IMenuTitleUIObserver
{
public:

	//		デストラクタ
	~IMenuTitleUIObserver() = default;

	/*
	*	タイトルの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	virtual void TitleMoveProcess(float move) = 0;

};