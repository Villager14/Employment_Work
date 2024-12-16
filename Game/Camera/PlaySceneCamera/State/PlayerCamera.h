/*
* @file		PlayerCamera.h
* @brief	プレイヤーのカメラ
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerCamera();
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;
	
	//		状態の遷移の確認
	void ChangeStateConfirmation();

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		始点の座標
	DirectX::SimpleMath::Vector3 m_position;
};
