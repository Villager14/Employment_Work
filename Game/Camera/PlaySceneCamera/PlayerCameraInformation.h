/*
* @file		PlayerCameraInformation.cpp
* @brief	プレイヤーのカメラの情報
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "pch.h"

class PlayerCameraInformation
{
public:
	//		コンストラクタ
	PlayerCameraInformation()
		:
		m_angleMin(0.0f)
	{};

	//		デストラクタ
	~PlayerCameraInformation() {};


private:

	//		最大角度Y
	const float ANGLE_Y_MAX = 50.0f;

	//		最小角度Y
	const float ANGLE_Y_MIN = -50.0f;

	//		カメラの速度
	const float CAMERA_SPEED = 5.0f;

	//		視野角最大
	const float VIEWING_ANGLE_MAX = 90.0f;

	//		視野角最小
	const float VIEWING_ANGLE_MIN = 70.0f;

public:

	/*
	*	最大角度Yを受け取る
	*
	*	@return 角度
	*/
	float GetMaxAngleY() { return ANGLE_Y_MAX; }

	/*
	*	最小角度Yを受け取る
	*
	*	@return 角度
	*/
	float GetMinAngleY() { return ANGLE_Y_MIN; }

	/*
	*	カメラの速度を受け取る
	*
	*	@return 速度
	*/
	float GetCameraSpeed() { return CAMERA_SPEED; }

private:

	//		最小値
	float m_angleMin;

	//		カメラの角度
	DirectX::SimpleMath::Vector2 m_angle;

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		カメラの移動量
	DirectX::SimpleMath::Vector2 m_cameraMove;

public:

	/*
	*	カメラの角度を受けとる
	*
	*	@return 角度
	*/
	const DirectX::SimpleMath::Vector2 GetAngle() { return m_angle; }

	/*
	*	カメラの角度を設定する
	*
	*	@param	(angle)	角度
	*/
	void SetAngle(DirectX::SimpleMath::Vector2 angle) { m_angle = angle; }

	/*
	*	視線ベクトルを設定する
	*
	*	@param	(velocity)	ベクトル
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& velicity) { m_viewVelocity = velicity; }

	/*
	*	視線ベクトルを受け取る
	*
	*	@return ベクトル
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	視野角最小角度を受け取る
	*
	*	@return 角度
	*/
	const float GetViewingAngleMin() { return VIEWING_ANGLE_MIN; }

	/*
	*	視野角最大角度を受け取る
	*
	*	@return 角度
	*/
	const float GetViewingAngleMax() { return VIEWING_ANGLE_MAX; }

	/*
	*	Eyeベクトルを設定する
	*
	*	@param	(eye)	視線ベクトル
	*/
	void SetEye(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }

	/*
	*	Eyeベクトルを受け取る
	*
	*	@return 視線ベクトル
	*/
	DirectX::SimpleMath::Vector3 GetEye() { return m_eye; }

	/*
	*	ターゲットを設定する
	*
	*	@param	(target)	ターゲットベクトル
	*/
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	/*
	*	ターゲットを受け取る
	*
	*	@return ターゲット
	*/
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }

	/*
	*	アップベクトルを設定する
	*
	*	@param	(up)	アップベクトル
	*/
	void SetUp(DirectX::SimpleMath::Vector3 up) { m_up = up; }

	/*
	*	アップベクトルを受け取る
	*
	*	@return アップベクトル
	*/
	DirectX::SimpleMath::Vector3 GetUP() { return m_up; }

	/*
	*	カメラの移動量を設定する
	*
	*	@param	(move)	移動量
	*/
	void SetCameraMove(DirectX::SimpleMath::Vector2 move) { m_cameraMove = move; }

	/*
	*	カメラの移動量を受け取る
	*
	*	@return 移動量
	*/
	DirectX::SimpleMath::Vector2 GetCameraMove() { return m_cameraMove; }

	/*
	*	カメラ角度の最小値を受け取る
	*
	*	@return 最小値
	*/
	float GetCameraAngleMin() { return m_angleMin; }

	/*
	*	カメラ角度の最小値を設定する
	* 
	*	@param	(angle)	角度
	*/
	void SetCameraAngleMin(float angle) { m_angleMin = angle; }
};
