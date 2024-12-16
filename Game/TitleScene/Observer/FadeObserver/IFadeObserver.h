/*
* @file		IFadeObserver.h
* @brief	�t�F�[�h�I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "pch.h"

class IFadeObserver
{
public:

	//		�f�X�g���N�^
	~IFadeObserver() = default;

	//		�V�[���I���t�F�[�h�A�E�g
	virtual void SceneEndFadeOut() = 0;

	//		�t�F�[�h�A�E�g
	virtual void FadeOut() = 0;
};