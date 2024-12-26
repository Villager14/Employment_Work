/*
* @file		MenuTitleUIObserver.h
* @brief	���j���[�̃^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuTitleUIObserver.h"

class MenuTitleUIObserver
{
public:

	//		�R���X�g���N�^
	MenuTitleUIObserver();

	//		�f�X�g���N�^
	~MenuTitleUIObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuTitleUIObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuTitleUIObserver* observer);

	/*
	*	�^�C�g���̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void TitleMoveProcess(float move);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuTitleUIObserver*> m_observer;

};