/*
* @file		IMouseKeyInputObserver.h
* @brief	マウスのキー入力オブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "pch.h"

#include "../MouseList.h"

class IMouseKeyInputObserver
{
public:

	//		デストラクタ
	~IMouseKeyInputObserver() = default;

	/*
	*	マウスの押した瞬間の処理
	* 
	*	@param	(key)	押したキー
	*/
	virtual void IsKeyPressed(KeyInputMouse::MouseList key) = 0;

	/*
	*	マウスの離した瞬間の処理
	*
	*	@param	(key)	離したキー
	*/
	virtual void IsKeyReleased(KeyInputMouse::MouseList key) = 0;

	/*
	*	マウスの押し続けたの時の処理
	*
	*	@param	(key)	押し続けたキー
	*/
	virtual void IsKeepPushing(KeyInputMouse::MouseList key) = 0;
};