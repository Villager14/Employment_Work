/*
* @file		IMenuTabUIObserver.h
* @brief	���j���[��TabUI�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/19
*/
#pragma once

#include "pch.h"

#include "../../UI/MenuUITabEnums.h"

class IMenuTabUIObserver
{
public:

	//		�f�X�g���N�^
	~IMenuTabUIObserver() = default;

	/*
	*	�^�uUI�̈ړ�
	*
	*	@param	(move)	�ړ���(0~1)
	*/
	virtual void TabMove(float move) = 0;

	/*
	*	�^�u���g�����ǂ���
	* 
	*	@param	(bool) true : �g�� false : �g��Ȃ�
	*/
	virtual void TabUseJudgement(float judgement) = 0;
};