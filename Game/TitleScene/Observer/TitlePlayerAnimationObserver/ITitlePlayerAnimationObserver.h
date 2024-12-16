/*
* @file		ITitlePlayerAnimationObserver.h
* @brief	�^�C�g���̃v���C���[�A�j���[�V�����I�u�U�[�o�[�̃C���^�[�t�F�C�X
* @author	Morita
* @date		2024/12/12
*/

#pragma once

class ITitlePlayerAnimationObserver
{
public:

	//		�f�X�g���N�^
	~ITitlePlayerAnimationObserver() = default;

	//		�v���C���̃A�j���[�V����
	virtual void PlayAnimation() = 0;

	//		�ݒ莞�̃A�j���[�V����
	virtual void SettingAnimation() = 0;

	//		�I�����̃A�j���[�V����
	virtual void ExitAnimation() = 0;
};