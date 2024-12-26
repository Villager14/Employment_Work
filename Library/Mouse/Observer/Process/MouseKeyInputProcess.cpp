/*
* @file		MouseKeyInputProcess.cpp
* @brief	マウスのキー入力処理
* @author	Morita
* @date		2024/12/24
*/

#include "pch.h"

#include "MouseKeyInputProcess.h"

MouseKeyInputProcess::MouseKeyInputProcess()
{
}

MouseKeyInputProcess::~MouseKeyInputProcess()
{
}

bool MouseKeyInputProcess::InputProcess(DirectX::Mouse::ButtonStateTracker::ButtonState buttonState, KeyInputMouse::MouseState state)
{
	//		左クリックの場合
	if (state == KeyInputMouse::MouseState::leftButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton == buttonState)
		{
			return true;
		}
	}
	//		右クリックの場合
	else if (state == KeyInputMouse::MouseState::rightButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->rightButton == buttonState)
		{
			return true;
		}
	}
	//		左クリックの場合（押し込み）
	else if (state == KeyInputMouse::MouseState::keepLeftButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().leftButton)
		{
			return true;
		}
	}
	//		右クリックの場合（押し込み）
	else if (state == KeyInputMouse::MouseState::keepRightButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().rightButton)
		{
			return true;
		}
	}

	return false;
}