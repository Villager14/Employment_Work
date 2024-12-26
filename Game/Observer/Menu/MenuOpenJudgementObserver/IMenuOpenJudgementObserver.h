/*
* @file		IMenuOpenJudgementObserver.h
* @brief	���j���[���J���Ă��邩���f����I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuOpenJudgementObserver
{
public:

	//		�f�X�g���N�^
	~IMenuOpenJudgementObserver() = default;

	//		���j���[���J���Ă���
	virtual void MenuOpen() = 0;

	//		���j���[����Ă���
	virtual void MenuClose() = 0;
};