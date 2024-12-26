/*
* @file		MenuUsedObserver.h
* @brief	���j���[���g���邩���f����I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuUsedObserver.h"

class MenuUsedObserver
{
public:

	//		�R���X�g���N�^
	MenuUsedObserver();

	//		�f�X�g���N�^
	~MenuUsedObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuUsedObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuUsedObserver* observer);

	//		���j���[���g�����Ƃ��ł��邩���f����
	void MenuUseJudgement(bool judgement);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuUsedObserver*> m_observer;

};