/*
* @file		MouseKeyInput.h
* @brief	�}�E�X�̃L�[����
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "Observer/MouseKeyInputObserver.h"

class MouseKeyInput
{
public:

	//		�R���X�g���N�^
	MouseKeyInput();

	//		�f�X�g���N�^
	~MouseKeyInput();

	//		�X�V����
	void Update();

	void Finalize();

private:

	//		�}�E�X�̃L�[���̓I�u�U�[�o�[
	std::unique_ptr<MouseKeyInputObserver> m_mouseKeyInputObserver;

public:

	/*
	*	�}�E�X�̃L�[���̓I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	MouseKeyInputObserver* GetMouseKeyInputObserver() { return m_mouseKeyInputObserver.get(); }
};