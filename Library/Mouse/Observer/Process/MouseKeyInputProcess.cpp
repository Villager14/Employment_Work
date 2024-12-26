/*
* @file		MouseKeyInputProcess.cpp
* @brief	�}�E�X�̃L�[���͏���
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
	//		���N���b�N�̏ꍇ
	if (state == KeyInputMouse::MouseState::leftButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->leftButton == buttonState)
		{
			return true;
		}
	}
	//		�E�N���b�N�̏ꍇ
	else if (state == KeyInputMouse::MouseState::rightButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->rightButton == buttonState)
		{
			return true;
		}
	}
	//		���N���b�N�̏ꍇ�i�������݁j
	else if (state == KeyInputMouse::MouseState::keepLeftButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().leftButton)
		{
			return true;
		}
	}
	//		�E�N���b�N�̏ꍇ�i�������݁j
	else if (state == KeyInputMouse::MouseState::keepRightButton)
	{
		if (LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().rightButton)
		{
			return true;
		}
	}

	return false;
}