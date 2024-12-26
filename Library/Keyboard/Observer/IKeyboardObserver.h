/*
* @file		IKeyboardObserver.h
* @brief	キーボードオブザーバーのインターフェイス
* @author	Morita
* @date		2024/12/21
*/

#pragma once

#include "pch.h"

#include "../KeyboardList.h"

class IKeyboardObserver
{
public:

	//		デストラクタ
	~IKeyboardObserver() = default;

	/*
	*	キーボードの押した瞬間の処理
	* 
	*	@param	(key)	押したキー
	*/
	virtual void IsKeyPressed(KeyboardList::KeyboardList key) = 0;

	/*
	*	キーボードの離した瞬間の処理
	*
	*	@param	(key)	押したキー
	*/
	virtual void IsKeyReleased(KeyboardList::KeyboardList key) = 0;

	/*
	*	キーボードの押している時の処理
	*
	*	@param	(key)	押したキー
	*/
	virtual void IsKeyState(KeyboardList::KeyboardList key) = 0;

};