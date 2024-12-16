/*
* @file		TitlePlayerAnimationObserver.cpp
* @brief	�v���C���[�̃A�j���V�����I�u�U�[�o�[
* @author	Morita
* @date		2024/12/16
*/

#pragma once

#include "ITitlePlayerAnimationObserver.h"

class TitlePlayerAnimationObserver
{
public:

	//		�R���X�g���N�^
	TitlePlayerAnimationObserver();

	//		�f�X�g���N�^
	~TitlePlayerAnimationObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(ITitlePlayerAnimationObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(ITitlePlayerAnimationObserver* observer);

	//		�f���[�g
	void Dalete();

	//		�v���C���̃A�j���[�V����
	void PlayAnimation();

	//		�ݒ莞�̃A�j���[�V����
	void SettingAnimation();

	//		�I�����̃A�j���[�V����
	void ExitAnimation();

private:

	//		�I�u�U�[�o�[
	std::vector<ITitlePlayerAnimationObserver*> m_observer;

};
