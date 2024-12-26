/*
* @file		MenuMouseObserver.h
* @brief	���j���[�̃}�E�X�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuMouseObserver.h"

class MenuMouseObserver
{
public:

	//		�R���X�g���N�^
	MenuMouseObserver();

	//		�f�X�g���N�^
	~MenuMouseObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuMouseObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuMouseObserver* observer);

	/*
	*	�}�E�X��X���W�̍X�V
	*
	*	@param	(x) x���W
	*/
	void MousePositionX(int x);

	/*
	*	�}�E�X��Y���W�̍X�V
	*
	*	@param	(y) y���W
	*/
	void MousePositionY(int y);


	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuMouseObserver*> m_observer;

};