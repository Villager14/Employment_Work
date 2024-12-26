/*
* @file		MouseKeyInputObserver.cpp
* @brief	�}�E�X�̃L�[���̓I�u�U�[�o�[
* @author	Morita
* @date		2024/12/22
*/

#include "pch.h"

#include "MouseKeyInputObserver.h"

MouseKeyInputObserver::MouseKeyInputObserver()
{
	//		�}�E�X�̓��͏����̐���
	m_keyInputProcess = std::make_unique<MouseKeyInputProcess>();
}

MouseKeyInputObserver::~MouseKeyInputObserver()
{
}

void MouseKeyInputObserver::AddPressedObserver(IMouseKeyInputObserver* observer,
												KeyInputMouse::MouseState state,
												KeyInputMouse::MouseList key)
{
	//		�I�u�U�[�o�[��ǉ�
	m_pressedObserver[key] = { observer, state };
}

void MouseKeyInputObserver::AddReleasedObserver(IMouseKeyInputObserver* observer,
												KeyInputMouse::MouseState state,
												KeyInputMouse::MouseList key)
{
	//		�I�u�U�[�o�[��ǉ�
	m_releasedObserver[key] = { observer, state };
}

void MouseKeyInputObserver::AddKeepPushingObserver(IMouseKeyInputObserver* observer,
													KeyInputMouse::MouseState state,
													KeyInputMouse::MouseList key)
{
	//		�I�u�U�[�o�[��ǉ�
	m_keepPushingObserver[key] = { observer, state };
}

void MouseKeyInputObserver::DeletePressedObserver(KeyInputMouse::MouseList keyboard)
{
	//		�L�[������ꍇ�������s��
	if (m_pressedObserver.find(keyboard) != m_pressedObserver.end())
	{
		//		�I�u�U�[�o�[�̍폜
		m_pressedObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::DeleteReleasedObserver(KeyInputMouse::MouseList keyboard)
{
	//		�L�[������ꍇ�������s��
	if (m_releasedObserver.find(keyboard) != m_releasedObserver.end())
	{

		//		�I�u�U�[�o�[�̍폜
		m_releasedObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::DeleteKeepPushingObserver(KeyInputMouse::MouseList keyboard)
{
	//		�L�[������ꍇ�������s��
	if (m_keepPushingObserver.find(keyboard) != m_keepPushingObserver.end())
	{

		//		�I�u�U�[�o�[�̍폜
		m_keepPushingObserver.erase(keyboard);
	}
}

void MouseKeyInputObserver::IsKeyPressed()
{
	for (const auto& e : m_pressedObserver)
	{
		//		�L�[���������ꍇ
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().PRESSED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::IsKeyReleased()
{
	for (const auto& e : m_releasedObserver)
	{
		//		�L�[���������ꍇ
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().RELEASED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::IsKeepPushing()
{
	for (const auto& e : m_keepPushingObserver)
	{
		//		�L�[���������ꍇ
		if (m_keyInputProcess->InputProcess(DirectX::Mouse::ButtonStateTracker().RELEASED,
			e.second.second))
		{
			e.second.first->IsKeyPressed(e.first);
		}
	}
}

void MouseKeyInputObserver::Dalete()
{
	//		�S�Ă��폜����
	m_pressedObserver.clear();
	m_releasedObserver.clear();
	m_keepPushingObserver.clear();
}