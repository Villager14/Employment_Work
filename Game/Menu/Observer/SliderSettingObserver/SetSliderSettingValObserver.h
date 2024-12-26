/*
* @file		SetSliderSettingValObserver.cpp
* @brief	�X���C�_�[�̒l��ݒ�ɑ���I�u�U�[�o�[
* @author	Morita
* @date		2024/12/26
*/

#pragma once

#include "ISetSliderSettingValObserver.h"

class SetSliderSettingValObserver
{
public:

	//		�R���X�g���N�^
	SetSliderSettingValObserver();

	//		�f�X�g���N�^
	~SetSliderSettingValObserver();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(ISetSliderSettingValObserver* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(ISetSliderSettingValObserver* observer);

	/*
	*	����p�̒l���󂯎��
	*
	*	@param	(val)�@����̊���
	*/
	void SetFov(float val);

	/*
	*	�}�E�X���x���󂯎��
	*
	*	@param	(val)�@���x�̊���
	*/
	void SetMouseSensitivity(float val) ;


	//		�S�폜
	void Dalete();

private:

	std::vector<ISetSliderSettingValObserver*> m_observer;

};