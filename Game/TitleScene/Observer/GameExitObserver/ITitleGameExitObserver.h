/*
* @file		ITitleGameExitObserver.h
* @brief	�^�C�g���Q�[���I���I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class ITitleGameExitObserver
{
public:

	//		�f�X�g���N�^
	~ITitleGameExitObserver() = default;

	//		�Q�[�����I������
	virtual void GameExit() = 0;
};