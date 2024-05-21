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
	m_startJudgement(false)
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

	//		カメラの角度
	DirectX::SimpleMath::Vector2 m_angle;

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	//		開始するかどうか
	bool m_startJudgement;
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
	*	開始するかどうか受け取る
	* 
	*	@return true : 開始 false : 開始していない
	*/
	bool GetStartJudgement() { return m_startJudgement; }

	/*
	*	開始するかどうか設定する
	*
	*	@param (judgement) true : 開始 false : 開始していない
	*/
	void GetStartJudgement(bool judgement) { m_startJudgement = judgement; }

};
