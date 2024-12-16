/*
* @file		PlayerGoalCamera.h
* @brief	プレイヤーのゴールカメラ
* @author	Morita
* @date		2024/06/27
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerGoalCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerGoalCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerGoalCamera();
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

	//		カメラの移動
	void CameraMove();

private:

	//		下を向いた時の角度
	const float DOWN_VIEW_ANGLE = -50.0f;

	//		平行角度最大時間
	const float PARALLEL_MAXIMUM_TIME = 2.0f;

	//		平行角度速度
	const float PARALLEL_MAXIMUM_SPEED = 2.0f;

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		角度
	DirectX::SimpleMath::Vector2 m_angle;

	//		経過時間
	float m_elapsedTime;

	//		下を向く時間
	float m_downElapsedTime;
};
