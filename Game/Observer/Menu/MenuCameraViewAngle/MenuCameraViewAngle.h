/*
* @file		MenuCameraViewAngle.h
* @brief	���j���[�̃J�����̎���p���󂯎��I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuCameraViewAngle.h"

class MenuCameraViewAngle
{
public:

	//		�R���X�g���N�^
	MenuCameraViewAngle();

	//		�f�X�g���N�^
	~MenuCameraViewAngle();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuCameraViewAngle* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuCameraViewAngle* observer);

	//		���j���[�̃J�����̎���p���󂯎��
	void GetMenuCameraViewAngle(float angle);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuCameraViewAngle*> m_observer;

};