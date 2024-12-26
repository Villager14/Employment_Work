/*
* @file		MenuCameraSpeed.cpp
* @brief	���j���[�̃J�����̑��x���󂯎��I�u�U�[�o�[
* @author	Morita
* @date		2024/12/23
*/

#pragma once

#include "IMenuCameraSpeed.h"

class MenuCameraSpeed
{
public:

	//		�R���X�g���N�^
	MenuCameraSpeed();

	//		�f�X�g���N�^
	~MenuCameraSpeed();

	/*
	*	�I�u�U�[�o�[�̒ǉ�
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddObserver(IMenuCameraSpeed* observer);

	/*
	*	�I�u�U�[�o�[�̍폜
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void DeleteObserver(IMenuCameraSpeed* observer);

	//		���j���[�̃J�����̑��x
	void GetMenuCameraSpeed(float speed);

	//		�S�폜
	void Dalete();
private:

	std::vector<IMenuCameraSpeed*> m_observer;

};