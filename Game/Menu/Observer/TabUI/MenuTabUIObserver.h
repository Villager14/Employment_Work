/*
* @file		MenuTabUIObserver.h
* @brief	���j���[��TabUI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/19
*/

#pragma once

#include "IMenuTabUIObserver.h"

class MenuTabUIObserver
{
public:

	//		�R���X�g���N�^
	MenuTabUIObserver();

	//		�f�X�g���N�^
	~MenuTabUIObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuTabUIObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuTabUIObserver* observer);

	/*
	*	�^�uUI�̈ړ�
	*
	*	@param	(move)	�ړ���(0~1)
	*/
	void TabMove(float move);

	/*
	*	�^�u���g�����ǂ���
	*
	*	@param	(bool) true : �g�� false : �g��Ȃ�
	*/
	void TabUseJudgement(float judgement);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuTabUIObserver*> m_observer;

};