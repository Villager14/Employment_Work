/*
* @file		TitleUIObserver.h
* @brief	�^�C�g��UI�I�u�U�[�o�[
* @author	Morita
* @date		2024/12/12
*/

#pragma once

#include "ITitleUIObserver.h"

class TitleUIObserver
{
public:

	//		�R���X�g���N�^
	TitleUIObserver();

	//		�f�X�g���N�^
	~TitleUIObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void AddObserver(ITitleUIObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[
	*/
	void DeleteObserver(ITitleUIObserver* observer);

	/*
	*	����I������
	*
	*	@param	(processingTime)	��������
	*/
	void DownSelect(float processingTime);

	/*
	*	���I������
	*
	*	@param	(processingTime)	��������
	*/
	void UpSelect(float processingTime);

	//		�S�폜
	void Dalete();

private:

	//		�I�u�U�[�o�[
	std::vector<ITitleUIObserver*> m_observer;
};