/*
* @file		ITitleMenuUseObserver.h
* @brief	���j���[���g�����̃I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "pch.h"

class ITitleMenuUseObserver
{
public:

	//		�f�X�g���N�^
	~ITitleMenuUseObserver() = default;


	//		���j���[���g��
	virtual void OpenMenu() = 0;

	//		���j���[���g�p�ł���悤�ɂ���
	virtual void EnableMenu() = 0;

	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	virtual void DisableMenu() = 0;
};