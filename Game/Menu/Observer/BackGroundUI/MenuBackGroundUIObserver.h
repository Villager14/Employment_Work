/*
* @file		MenuBackGroundUIObserver.h
* @brief	���j���[�̔w�iUI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuBackGroundUIObserver.h"

class MenuBackGroundUIObserver
{
public:

	//		�R���X�g���N�^
	MenuBackGroundUIObserver();

	//		�f�X�g���N�^
	~MenuBackGroundUIObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuBackGroundUIObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuBackGroundUIObserver* observer);

	/*
	*	�o�[�̃X�P�[���̕ύX
	*
	*	@param	(float scale)
	*/
	void BarScale(float scale);

	/*
	*	���j���[�̓�������
	*
	*	@param	(move)	�ړ��ʁi0~1�j
	*/
	void MenuMoveProcess(float move);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuBackGroundUIObserver*> m_observer;

};