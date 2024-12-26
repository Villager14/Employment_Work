/*
* @file		MenuMouseProcess.h
* @brief	���j���[�̃}�E�X����
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "../Observer/Mouse/MenuMouseObserver.h"

class MenuMouseProcess
{
public:

	//		�R���X�g���N�^
	MenuMouseProcess();

	//		�f�X�g���N�^
	~MenuMouseProcess();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�I������
	void Finalize();

private:
	//		���j���[�}�E�X�I�u�U�[�o�[
	std::unique_ptr<MenuMouseObserver> m_menuMouseObserver;

	//		�}�E�X�̍��WX
	int m_mousePositionX;

	//		�}�E�X�̍��WY
	int m_mousePositionY;

public:

	/*
	*	�}�E�X�I�u�U�[�o�[�ɒǉ�����
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddMenuMouseObserver(IMenuMouseObserver* observer) { m_menuMouseObserver->AddObserver(observer); }

};