/*
* @file		MenuIconUIObserver.cpp
* @brief	���j���[�̃A�C�R��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/20
*/

#pragma once

#include "IMenuIconUIObserver.h"

class MenuIconUIObserver
{
public:

	//		�R���X�g���N�^
	MenuIconUIObserver();

	//		�f�X�g���N�^
	~MenuIconUIObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuIconUIObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuIconUIObserver* observer);

	/*
	*	�A�C�R���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void IconMoveProcess(float move);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuIconUIObserver*> m_observer;

};