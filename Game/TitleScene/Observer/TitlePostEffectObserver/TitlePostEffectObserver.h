/*
* @file		TitlePostEffectObserver.h
* @brief	�|�X�g�G�t�F�N�g�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitlePostEffectObserver.h"

class TitlePostEffectObserver
{
public:

	//		�R���X�g���N�^
	TitlePostEffectObserver();

	//		�f�X�g���N�^
	~TitlePostEffectObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(ITitlePostEffectObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	* 
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(ITitlePostEffectObserver* observer);

	//		�t�F�[�h�C��
	void FadeIn();

	//		�t�F�[�h�A�E�g
	void FadeOut();

	//		�f���[�g
	void Dalete();

private:

	//		�I�u�U�[�o�[
	std::vector<ITitlePostEffectObserver*> m_observer;

};
