/*
* @file		MouseKeyInputObserver.h
* @brief	�}�E�X�̃L�[���̓I�u�U�[�o�[
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "IMouseKeyInputObserver.h"

#include "../MouseList.h"

#include "Process/MouseKeyInputProcess.h"

class MouseKeyInputObserver
{
public:

	//		�R���X�g���N�^
	MouseKeyInputObserver();

	//		�f�X�g���N�^
	~MouseKeyInputObserver();

	/*
	*	�}�E�X�̉��������̃I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)		�I�u�U�[�o�[
	*	@param	(buttonState)	�}�E�X����
	*	@param	(key)			�g�p����L�[
	*/
	void AddPressedObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	�}�E�X�̗��������̃I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)		�I�u�U�[�o�[
	*	@param	(buttonState)	�}�E�X����
	*	@param	(key)			�g�p����L�[
	*/
	void AddReleasedObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	�}�E�X�̉����������̎��̃I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)		�I�u�U�[�o�[
	*	@param	(buttonState)	�}�E�X����
	*	@param	(key)			�g�p����L�[
	*/
	void AddKeepPushingObserver(IMouseKeyInputObserver* observer,
		KeyInputMouse::MouseState state, KeyInputMouse::MouseList key);

	/*
	*	�}�E�X���L�[���������Ƃ��̃I�u�U�[�o�[�̍폜
	*
	*	@param	(MouseList)	�}�E�X�̃L�[
	*/
	void DeletePressedObserver(KeyInputMouse::MouseList keyboard);

	/*
	*	�}�E�X���L�[�𗣂������̃I�u�U�[�o�[�̍폜
	*
	*	@param	(MouseList)	�}�E�X�̃L�[
	*/
	void DeleteReleasedObserver(KeyInputMouse::MouseList keyboard);

	/*
	*	�}�E�X�̉����������̃I�u�U�[�o�[�̍폜
	*
	*	@param	(MouseList)	�}�E�X�̃L�[
	*/
	void DeleteKeepPushingObserver(KeyInputMouse::MouseList keyboard);

	//	�}�E�X�̉������u�Ԃ̏���
	void IsKeyPressed();

	//	�}�E�X�̗������u�Ԃ̏���
	void IsKeyReleased();

	//	�}�E�X�̉������������̏���
	void IsKeepPushing();

	//		�S�폜
	void Dalete();

private:

	//		�}�E�X�̓��͏���
	std::unique_ptr<MouseKeyInputProcess> m_keyInputProcess;

	//		�}�E�X���������Ƃ��̃I�u�U�[�o�[
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_pressedObserver;

	//		�}�E�X�̗������Ƃ��̃L�[�I�u�U�[�o�[
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_releasedObserver;

	//		�}�E�X�̉����������̎��̃L�[�I�u�U�[�o�[
	std::unordered_map<KeyInputMouse::MouseList, std::pair<IMouseKeyInputObserver*, KeyInputMouse::MouseState>> m_keepPushingObserver;
};