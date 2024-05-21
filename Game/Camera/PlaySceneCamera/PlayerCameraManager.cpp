/*
* @file		PlayerCameraManager.cpp
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager()
	:
	m_state{}
{
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize()
{
	//		デバックカメラの生成
	m_debugCamera = std::make_unique<DebugCamera>(this);
	//		プレイヤーカメラの生成
	m_playerCamera = std::make_unique<PlayerCamera>(this);
	//		プレイヤー壁走りカメラの生成
	m_playerWallWalkCamera = std::make_unique<PlayerWallWalkCamera>(this);

	//		初期カメラの選択
	m_state = m_playerCamera.get();

	//		初期化処理
	m_state->Initialize();

	/*
	*	視野角70度
	*
	*	近い距離0.1f
	* 　遠い距離500.0f
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(50.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 500.0f);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void PlayerCameraManager::Update(PlayerInformationCamera* playerInformationCamera)
{
	m_playerInformationCamera = playerInformationCamera;

	//		カメラの更新処理
	m_state->Update();

	ViewingAngle();
}

void PlayerCameraManager::Finalize()
{
}

void PlayerCameraManager::CameraMove()
{
	//		マウスの相対位置から移動量を出す
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		カメラの移動量を足す
	m_angle.x += x * CAMERA_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
	m_angle.y += -y * (CAMERA_SPEED / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		視点移動の制限
	m_angle.y = Library::Clamp(m_angle.y, ANGLE_Y_MIN, ANGLE_Y_MAX);
	
}

void PlayerCameraManager::ChangeState(IPlayerCamera* state)
{
	//		同じ状態なら処理をしない
	if (m_state == state) return;

	//		現在の状態の終了処理を行う
	m_state->Finalize();

	//		新しい状態にする
	m_state = state;

	//		新しい状態の初期化をする
	m_state->Initialize();
}

void PlayerCameraManager::ViewingAngle()
{
	if (m_playerInformationCamera->GetAcceleration().Length() > 50.0f)
	{
		float time = Library::Clamp(((m_playerInformationCamera->GetAcceleration().Length() - 50.0f) / 60.0f), 0.0f, 1.0f);

		float viewAnge = Library::Lerp(50.0f, 55.0f, time);

		/*
		*	視野角70度
		*
		*	近い距離0.1f
		* 　遠い距離500.0f
		*/
		DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
			CreatePerspectiveFieldOfView
			(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
				LibrarySingleton::GetInstance()->GetScreenSize().y,
				0.1f, 500.0f);

		//		プロジェクション行列を設定する
		LibrarySingleton::GetInstance()->SetProj(proj);
	}
}
