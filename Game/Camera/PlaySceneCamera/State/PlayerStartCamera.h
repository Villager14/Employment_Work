/*
* @file		PlayerStartCamera.h
* @brief	プレイヤースタートカメラ
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerStartCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerStartCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerStartCamera();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

	//		移動処理
	void Move();

	//		状態の遷移の確認
	void ChangeStateConfirmation();

private:

	//		状態遷移時間
	const float STATE_CHANGE_TIME = 1.0f;

	//		角度を上げる速度
	const float ANGLE_UP_SPEED = 0.5f;

	//		顔を下げている角度
	const float DOWN_ANGLE = -40.0f;
		
private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		時間
	float m_time;

	//		初期描画
	bool m_firstViewJudgement;
};
