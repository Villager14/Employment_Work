/*
* @file		GameSetting.h
* @brief	ゲームの設定
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
	//		メニューのカメラの視野角を生成する
	m_menuCameraViewAngle = std::make_unique<MenuCameraViewAngle>();

	//		メニューのカメラのカメラの速度を生成する
	m_menuCameraSpeed = std::make_unique<MenuCameraSpeed>();
}

GameSetting::~GameSetting()
{
}

void GameSetting::SetFov(float val)
{
	//		視野角の更新
	m_fov = Library::Lerp(FOV_MIN_VAL, FOV_MAX_VAL, val);

	//		視野角の更新
	m_menuCameraViewAngle->GetMenuCameraViewAngle(m_fov);
}

void GameSetting::SetMouseSensitivity(float val)
{
	//		マウスの感度の更新
	m_mouseSensitivitiy = Library::Lerp(MOUSE_SENSITIVITY_MIN, MOUSE_SENSITIVITY_MAX, val);

	//		マウスの感度の更新
	m_menuCameraSpeed->GetMenuCameraSpeed(m_mouseSensitivitiy);
}
