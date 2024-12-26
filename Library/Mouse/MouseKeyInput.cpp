/*
* @file		MouseKeyInput.cpp
* @brief	�}�E�X�̃L�[����
* @author	Morita
* @date		2024/12/22
*/

#include "pch.h"

#include "MouseKeyInput.h"

MouseKeyInput::MouseKeyInput()
{
	//		�}�E�X�̃L�[���̓I�u�U�[�o�[�̐���
	m_mouseKeyInputObserver = std::make_unique<MouseKeyInputObserver>();
}

MouseKeyInput::~MouseKeyInput()
{
}

void MouseKeyInput::Update()
{
	//		�������Ƃ��̏���
	m_mouseKeyInputObserver->IsKeyPressed();

	//		�������Ƃ��̏���
	m_mouseKeyInputObserver->IsKeyReleased();

	//		���������Ă���Ƃ��̏���
	m_mouseKeyInputObserver->IsKeepPushing();
}

void MouseKeyInput::Finalize()
{
	m_mouseKeyInputObserver->Dalete();
}
