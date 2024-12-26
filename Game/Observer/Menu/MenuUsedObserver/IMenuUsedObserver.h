/*
* @file		IMenuUsedObserver.h
* @brief	���j���[���g�����Ƃ��ł��邩���f����I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuUsedObserver
{
public:

	//		�f�X�g���N�^
	~IMenuUsedObserver() = default;

	//		���j���[���g�����Ƃ��ł��邩���f����
	virtual void MenuUseJudgement(bool judgement) = 0;
};