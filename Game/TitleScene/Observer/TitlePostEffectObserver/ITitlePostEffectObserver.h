/*
* @file		ITitlePostEffectObserver.h
* @brief	�^�C�g���|�X�g�G�t�F�N�g�̃I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class ITitlePostEffectObserver
{
public:

	//		�f�X�g���N�^
	~ITitlePostEffectObserver() = default;

	//		�t�F�[�h�C��
	virtual void FadeIn() = 0;

	//		�t�F�[�h�A�E�g
	virtual void FadeOut() = 0;

};