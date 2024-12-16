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
		m_angleMin(0.0f),
		m_viewAngle(70.0f),
		m_mouseSpeed(5.0f),
		m_nowViewAngle(0.0f),
		m_startDirection(0.0f),
		m_playerSpeed(0.0f),
		m_wallHeadMove(0.0f),
		m_direction(0.0f),
		m_stopJudgement(false),
		m_shakeHeadJudgement(false)
	{};

	//		デストラクタ
	~PlayerCameraInformation() {};

	void Initialize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_up = DirectX::SimpleMath::Vector3::Zero;
		m_target = DirectX::SimpleMath::Vector3::Zero;
		m_eye = DirectX::SimpleMath::Vector3::Zero;
		m_cameraMove = DirectX::SimpleMath::Vector2::Zero;
	}

public:

	//		最大角度Y
	const float ANGLE_Y_MAX = 50.0f;

	//		最小角度Y
	const float ANGLE_Y_MIN = -50.0f;

	//		視野を変更する最低速度
	const float ANGLE_CHANGE_MIN_SPEED = 30.0f;

	//		視野を変更する最高速度
	const float ANGLE_CHANGE_MAX_SPEED = 60.0f;

private:

	//		視野角
	float m_viewAngle;

	//		マウスの速度
	float m_mouseSpeed;

	//		最小値
	float m_angleMin;

	//		現在の視野角
	float m_nowViewAngle;

	//		開始時の方向
	float m_startDirection;

	//		プレイヤーの速度
	float m_playerSpeed;

	//		頭を動かす量
	float m_wallHeadMove;

	//		カメラを止めるかどうか
	bool m_stopJudgement;

	//		頭を揺らしているかどうか
	bool m_shakeHeadJudgement;

	//		カメラの角度
	DirectX::SimpleMath::Vector2 m_angle;

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		カメラの移動量
	DirectX::SimpleMath::Vector2 m_cameraMove;

	//		プレイヤーの高さ
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		プレイヤーの移動方向
	DirectX::SimpleMath::Vector3 m_direction;

	//		壁の法線
	DirectX::SimpleMath::Vector3 m_wallNormalize;

	//		頭を揺らすベクトル
	DirectX::SimpleMath::Vector3 m_shakeHeadVelocity;

public:

	/*
	*	視野角を設定する
	*
	*	@param	(angle)	角度
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	視野角を受け取る
	*
	*	@return	角度
	*/
	float GetViewAngle() { return m_viewAngle; }

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

	/*
	*	マウスの速度を受け取る
	*
	*	@return	速度
	*/
	float GetCameraSpeed() { return m_mouseSpeed; }

	/*
	*	マウスの速度を設定する
	*
	*	@param	(speed)
	*/
	void SetCameraSpeed(float speed) { m_mouseSpeed = speed; }

	/*
	*	現在の視野角を設定する
	*
	*	@param	(viewAngle)	視野角度
	*/
	void SetNowViewAngle(float viewAngle) { m_nowViewAngle = viewAngle; }

	/*
	*	現在の視野角を受け取る
	*
	*	@return 視野角
	*/
	float GetNowViewAngle() { return m_nowViewAngle; }

	/*
	*	開始時の方法を設定する
	*
	*	@param	(direction)	角度
	*/
	void SetStartDirection(float direction) { m_startDirection = direction; }

	/*
	*	開始時の方向を受け取る
	*
	*	@return 角度
	*/
	float GetStartDirection() { return m_startDirection; }

	/*
	*	プレイヤーの高さを受け取る
	*
	*	@return 高さ
	*/
	void SetPlayerHeight(DirectX::SimpleMath::Vector3 height) { m_playerHeight = height; }

	/*
	*	プレイヤーの高さを受け取る
	*
	*	@return 高さ
	*/
	DirectX::SimpleMath::Vector3 GetPlayerHeight() { return m_playerHeight; }

	/*
	*	プレイヤーの速度を設定する
	*
	*	@param	(speed)	速度
	*/
	void SetPlayerSpeed(float speed) { m_playerSpeed = speed; }

	/*
	*	プレイヤーの速度を受け取る
	*
	*	@return 速度
	*/
	float GetPlayerSpeed() { return m_playerSpeed; }

	/*
	*	頭を動かす量を設定する
	*
	*	@param	(move)	移動量
	*/
	void SetWallHeight(float move) { m_wallHeadMove = move; }

	/*
	*	頭を動かす量を受け取る
	*
	*	@return 移動量
	*/
	float GetWallHeight() { return m_wallHeadMove; }


	/*
	*	プレイヤーの移動方向を設定する
	*
	*	@param	(direction)	移動方向
	*/
	void SetDirection(DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }

	/*
	*	プレイヤーの移動方向受け取る
	*
	*	@return 移動方向
	*/
	DirectX::SimpleMath::Vector3 GetDirection() { return m_direction; }

	/*
	*	壁の法線を設定する
	*
	*	@param	(noramlize) 法線
	*/
	void SetWallNormalize(DirectX::SimpleMath::Vector3 normalize) { m_wallNormalize = normalize; }

	/*
	*	壁の法線を受け取る
	*
	*	@return 法線
	*/
	DirectX::SimpleMath::Vector3 GetWallNormalize() { return m_wallNormalize; }

	/*
	*	停止しているか受け取る
	* 
	*	@return true : 停止している false : 停止していない
	*/
	bool GetStopJudgement() { return m_stopJudgement; }

	/*
	*	停止しているか設定する
	* 
	*	@param	(judgement) true : 停止している false : 停止していない
	*/
	void SetStopJudgement(bool judgement) { m_stopJudgement = judgement; }

	/*
	*	頭を揺らすベクトルを受け取る
	* 
	*	@return ベクトル
	*/
	DirectX::SimpleMath::Vector3 GetShaekHeadVelocity() { return m_shakeHeadVelocity; }

	/*
	*	頭を揺らすベクトルを設定する
	* 
	*	@param	(velocity)	ベクトル
	*/
	void SetSheakHeadVelocity(DirectX::SimpleMath::Vector3 velocity) { m_shakeHeadVelocity = velocity; }

	/*
	*	頭を振るかどうか受け取る
	*
	*	@return	true : 頭を振っている false : 頭を振っていない
	*/
	bool GetShackHeadJudgement() { return m_shakeHeadJudgement; }

	/*
	*	頭を振るかどうか設定する
	* 
	*	@param	(judgement)	true : 頭を振っている false : 頭を振っていない
	*/
	void SetShackHeadJudgement(bool judgement) { m_shakeHeadJudgement = judgement; }
};
