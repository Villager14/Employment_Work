/*
* @file		GameSetting.h
* @brief	ゲームの設定
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

	//		コンストラクタ
	GameSetting();

	//		デストラクタ
	~GameSetting();

	/*
	*	視野角の値を受け取る
	*
	*	@param	(val)　視野の割合
	*/
	void SetFov(float val) override;

	/*
	*	マウス感度を受け取る
	*
	*	@param	(val)　感度の割合
	*/
	void SetMouseSensitivity(float val) override;

private:

	//		視野角の最大値
	const float FOV_MAX_VAL = 120.0f;

	//		視野角の最小値
	const float FOV_MIN_VAL = 70.0f;

	//		マウス感度最小値
	const float MOUSE_SENSITIVITY_MIN = 0.1f;

	//		マウス感度最大値
	const float MOUSE_SENSITIVITY_MAX = 10.0f;

private:

	//		視野角
	float m_fov;

	//		マウス感度
	float m_mouseSensitivitiy;


	//		メニューの視野角を受け取る
	std::unique_ptr<MenuCameraViewAngle> m_menuCameraViewAngle;

	//		メニューのカメラの速度
	std::unique_ptr<MenuCameraSpeed> m_menuCameraSpeed;

public:

	/*
	*	カメラの視野角のオブザーバーを追加する
	* 
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddCameraViewAngle(IMenuCameraViewAngle* observer) { m_menuCameraViewAngle->AddObserver(observer); }

	/*
	*	カメラの速度のオブザーバーを追加する
	*
	*	@param	(observer)	オブザーバーのインスタンスのポインタ
	*/
	void AddCameraSpeed(IMenuCameraSpeed* observer) { m_menuCameraSpeed->AddObserver(observer); }
};