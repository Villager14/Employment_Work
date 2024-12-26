/*
* @file		GameSetting.h
* @brief	�Q�[���̐ݒ�
* @author	Morita
* @date		2024/12/26
*/

#pragma once

#include "../Observer/SliderSettingObserver/ISetSliderSettingValObserver.h"

#include "Game/Observer/Menu/MenuCameraViewAngle/MenuCameraViewAngle.h"
#include "Game/Observer/Menu/MenuCameraSpeed/MenuCameraSpeed.h"

class GameSetting : public ISetSliderSettingValObserver
{
public:

	//		�R���X�g���N�^
	GameSetting();

	//		�f�X�g���N�^
	~GameSetting();

	/*
	*	����p�̒l���󂯎��
	*
	*	@param	(val)�@����̊���
	*/
	void SetFov(float val) override;

	/*
	*	�}�E�X���x���󂯎��
	*
	*	@param	(val)�@���x�̊���
	*/
	void SetMouseSensitivity(float val) override;

private:

	//		����p�̍ő�l
	const float FOV_MAX_VAL = 120.0f;

	//		����p�̍ŏ��l
	const float FOV_MIN_VAL = 70.0f;

	//		�}�E�X���x�ŏ��l
	const float MOUSE_SENSITIVITY_MIN = 0.1f;

	//		�}�E�X���x�ő�l
	const float MOUSE_SENSITIVITY_MAX = 10.0f;

private:

	//		����p
	float m_fov;

	//		�}�E�X���x
	float m_mouseSensitivitiy;


	//		���j���[�̎���p���󂯎��
	std::unique_ptr<MenuCameraViewAngle> m_menuCameraViewAngle;

	//		���j���[�̃J�����̑��x
	std::unique_ptr<MenuCameraSpeed> m_menuCameraSpeed;

public:

	/*
	*	�J�����̎���p�̃I�u�U�[�o�[��ǉ�����
	* 
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddCameraViewAngle(IMenuCameraViewAngle* observer) { m_menuCameraViewAngle->AddObserver(observer); }

	/*
	*	�J�����̑��x�̃I�u�U�[�o�[��ǉ�����
	*
	*	@param	(observer)	�I�u�U�[�o�[�̃C���X�^���X�̃|�C���^
	*/
	void AddCameraSpeed(IMenuCameraSpeed* observer) { m_menuCameraSpeed->AddObserver(observer); }
};