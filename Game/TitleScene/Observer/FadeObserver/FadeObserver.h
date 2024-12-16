/*
* @file		FadeObserver.h
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/


#pragma once

#include "IFadeObserver.h"

class FadeObserver
{
public:

	//		�R���X�g���N�^
	FadeObserver();

	//		�f�X�g���N�^
	~FadeObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(IFadeObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(IFadeObserver* observer);

	//		�t�F�[�h�A�E�g
	void SceneEndFadeOut();

	//		�t�F�[�h�A�E�g
	void FadeOut();

	//		�S�폜
	void Dalete();

private:

	//		�I�u�U�[�o�[
	std::vector<IFadeObserver*> m_observer;
};