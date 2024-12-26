/*
* @file		MouseKeyInputProcess.h
* @brief	マウスのキー入力処理
* @author	Morita
* @date		2024/12/24
*/

#pragma once

#include "../../MouseList.h"

class MouseKeyInputProcess
{
public:

	//		コンストラクタ
	MouseKeyInputProcess();

	//		デストラクタ
	~MouseKeyInputProcess();

	/*
	*	キー入力処理
	*
	*	@param	(buttonState)	ボタンのキー入力処理の種類
	*	@param	(state)			マウスの種類
	*	@return true : 処理が行われた false : 処理が行われていない
	*/
	bool InputProcess(DirectX::Mouse::ButtonStateTracker::ButtonState buttonState,
		KeyInputMouse::MouseState state);
};