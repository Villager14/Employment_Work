/*
* @file		TitleGameExitObserver.h
* @brief	�^�C�g���Q�[���I���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/13
*/

#pragma once

#include "ITitleGameExitObserver.h"

class TitleGameExitObserver
{
public:

	//		�R���X�g���N�^
	TitleGameExitObserver();

	//		�f�X�g���N�^
	~TitleGameExitObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(ITitleGameExitObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(ITitleGameExitObserver* observer);

	/*
	*	�Q�[���I��
	*/
	void GameExit();

	//		�S�폜
	void Dalete();

private:

	//		�I�u�U�[�o�[
	std::vector<ITitleGameExitObserver*> m_observer;
};