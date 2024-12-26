/*
* @file		MenuOpenJudgementObserver.cpp
* @brief	���j���[�J���Ă��邩���f����I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuOpenJudgementObserver.h"

class MenuOpenJudgementObserver
{
public:

	//		�R���X�g���N�^
	MenuOpenJudgementObserver();

	//		�f�X�g���N�^
	~MenuOpenJudgementObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuOpenJudgementObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuOpenJudgementObserver* observer);

	//		���j���[���J���Ă���
	void MenuOpen();

	//		���j���[����Ă���
	void MenuClose();

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuOpenJudgementObserver*> m_observer;

};