/*
* @file		IMenuMouseObserver.h
* @brief	メニューマウスオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "pch.h"

class IMenuMouseObserver
{
public:

	//		デストラクタ
	~IMenuMouseObserver() = default;

	/*
	*	マウスのX座標の更新
	* 
	*	@param	(x) x座標
	*/
	virtual void MousePositionX(int x) = 0;

	/*
	*	マウスのY座標の更新
	* 
	*	@param	(y) y座標
	*/
	virtual void MousePositionY(int y) = 0;
};