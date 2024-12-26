/*
* @file		MouseKeyInputProcess.h
* @brief	�}�E�X�̃L�[���͏���
* @author	Morita
* @date		2024/12/24
*/

#pragma once

#include "../../MouseList.h"

class MouseKeyInputProcess
{
public:

	//		�R���X�g���N�^
	MouseKeyInputProcess();

	//		�f�X�g���N�^
	~MouseKeyInputProcess();

	/*
	*	�L�[���͏���
	*
	*	@param	(buttonState)	�{�^���̃L�[���͏����̎��
	*	@param	(state)			�}�E�X�̎��
	*	@return true : �������s��ꂽ false : �������s���Ă��Ȃ�
	*/
	bool InputProcess(DirectX::Mouse::ButtonStateTracker::ButtonState buttonState,
		KeyInputMouse::MouseState state);
};