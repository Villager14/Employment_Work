/*
* @file		MenuColliderObserver.h
* @brief	���j���[�̓����蔻��I�u�U�[�o�[
* @author	Morita
* @date		2024/12/22
*/

#pragma once

#include "IMenuColliderObserver.h"

class MenuColliderObserver
{
public:

	//		�R���X�g���N�^
	MenuColliderObserver();

	//		�f�X�g���N�^
	~MenuColliderObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuColliderObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuColliderObserver* observer);

	/*
	*	��������UI�̃^�C�v
	*
	*	@param	(type)	UI�̃^�C�v
	*/
	void HitUIType(UISubType type);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuColliderObserver*> m_observer;

};