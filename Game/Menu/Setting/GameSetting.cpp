/*
* @file		GameSetting.h
* @brief	�Q�[���̐ݒ�
* @author	Morita
* @date		2024/12/26
*/

#include "pch.h"

#include "GameSetting.h"

GameSetting::GameSetting()
	:
	m_fov(0.0f),
	m_mouseSensitivitiy(0.0f)
{
	//		���j���[�̃J�����̎���p�𐶐�����
	m_menuCameraViewAngle = std::make_unique<MenuCameraViewAngle>();

	//		���j���[�̃J�����̃J�����̑��x�𐶐�����
	m_menuCameraSpeed = std::make_unique<MenuCameraSpeed>();
}

GameSetting::~GameSetting()
{
}

void GameSetting::SetFov(float val)
{
	//		����p�̍X�V
	m_fov = Library::Lerp(FOV_MIN_VAL, FOV_MAX_VAL, val);

	//		����p�̍X�V
	m_menuCameraViewAngle->GetMenuCameraViewAngle(m_fov);
}

void GameSetting::SetMouseSensitivity(float val)
{
	//		�}�E�X�̊��x�̍X�V
	m_mouseSensitivitiy = Library::Lerp(MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX, val);

	//		�}�E�X�̊��x�̍X�V
	m_menuCameraSpeed->GetMenuCameraSpeed(m_mouseSensitivitiy);
}
