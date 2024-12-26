/*
* @file		IMenuBackGroundUIObserver.h
* @brief	メニューの背景UIオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

class IMenuBackGroundUIObserver
{
public:

	//		デストラクタ
	~IMenuBackGroundUIObserver() = default;

	/*
	*	バーのスケールの変更
	*
	*	@param	(float scale)
	*/
	virtual void BackGroundBarScale(float scale) = 0;

	/*
	*	メニューの動く処理
	*
	*	@param	(move)	移動量（0~1）
	*/
	virtual void MenuMoveProcess(float move) = 0;

};