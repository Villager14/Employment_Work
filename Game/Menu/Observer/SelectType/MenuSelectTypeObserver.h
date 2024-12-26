/*
* @file		MenuSelectTypeObserver.h
* @brief	���j���[�̑I���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuSelectTypeObserver.h"

class MenuSelectTypeObserver
{
public:

	//		�R���X�g���N�^
	MenuSelectTypeObserver();

	//		�f�X�g���N�^
	~MenuSelectTypeObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuSelectTypeObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuSelectTypeObserver* observer);

	/*
	*	�I���^�C�v
	*
	*	@param	(type)�@�^�C�v
	*/
	void SelectType(MenuUITaype::UIType type);

	//		�S�폜
	void Dalete();

private:

	std::vector<IMenuSelectTypeObserver*> m_observer;

};