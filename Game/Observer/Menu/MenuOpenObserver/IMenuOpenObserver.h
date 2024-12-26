/*
* @file		IMenuOpenObserver.h
* @brief	���j���[���J���I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/23
*/
#pragma once

#include "pch.h"

class IMenuOpenObserver
{
public:

	//		�f�X�g���N�^
	~IMenuOpenObserver() = default;

	//		���j���[���J���Ă���
	virtual void MenuOpen() = 0;
};