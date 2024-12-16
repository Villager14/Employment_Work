/*
* @file		TitleUIObserver.h
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleMenuUseObserver.h"

class TitleMenuUseObserver
{
public:

	//		�R���X�g���N�^
	TitleMenuUseObserver();

	//		�f�X�g���N�^
	~TitleMenuUseObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(ITitleMenuUseObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(ITitleMenuUseObserver* observer);

	//		���j���[���g��
	void MenuUse();

	//		���j���[���g�p�ł���悤�ɂ���
	void EnableMenu();

	//		���j���[���g�p�ł��Ȃ��悤�ɂ���
	void DisableMenu();

	//		�S�폜
	void Dalete();

private:

	//		�I�u�U�[�o�[
	std::vector<ITitleMenuUseObserver*> m_observer;
};