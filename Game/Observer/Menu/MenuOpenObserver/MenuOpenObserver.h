/*
* @file		MenuOpenObserver.cpp
* @brief	���j���[�J���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuOpenObserver.h"

class MenuOpenObserver
{
public:

	//		�R���X�g���N�^
	MenuOpenObserver();

	//		�f�X�g���N�^
	~MenuOpenObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuOpenObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuOpenObserver* observer);

	//		���j���[���J���Ă���
	void MenuOpen();

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuOpenObserver*> m_observer;

};