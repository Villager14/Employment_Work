/*
* @file		PlayerCameraManager.cpp
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager(GameManager* gameManager)
	:
	m_state{},
	m_playerInformation{},
	m_gameManager(gameManager)
{
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize()
{
	//		カメラの情報を
	m_information = std::make_unique<PlayerCameraInformation>();

	//		デバックカメラの生成
	m_debugCamera = std::make_unique<DebugCamera>(this);
	//		プレイヤーカメラの生成
	m_playerCamera = std::make_unique<PlayerCamera>(this);
	//		プレイヤー壁走りカメラの生成
	m_playerWallWalkCamera = std::make_unique<PlayerWallWalkCamera>(this);
	//		プレイヤーのスタートカメラの生成
	m_playerStartCamera = std::make_unique<PlayerStartCamera>(this);
	//		プレイヤーの死亡カメラの生成
	m_playerDeathCamera = std::make_unique<PlayerDeathCamera>(this);

	//		初期カメラの選択
	//m_state = m_playerCamera.get();
	m_state = m_playerStartCamera.get();

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
		(DirectX::XMConvertToRadians(70.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 1000.0f);

	//		プロジェクション行列を設定する
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void PlayerCameraManager::Update(PlayerInformation* playerInformation)
{
	m_playerInformation = playerInformation;

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

	DirectX::SimpleMath::Vector2 angle = m_information->GetAngle();

	//		カメラの移動量を足す
	angle.x += x * m_information->GetCameraSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();
	angle.y += -y * (m_information->GetCameraSpeed() / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		視点移動の制限
	angle.y = Library::Clamp(angle.y, m_information->GetMinAngleY(), m_information->GetMaxAngleY());
	
	m_information->SetAngle(angle);

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
	if (m_playerInformation->GetAcceleration().Length() > 50.0f)
	{
		float time = Library::Clamp(((m_playerInformation->GetAcceleration().Length() - 50.0f) / 60.0f), 0.0f, 1.0f);

		float viewAnge = Library::Lerp(70.0f, 75.0f, time);

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
				0.1f, 1000.0f);

		//		プロジェクション行列を設定する
		LibrarySingleton::GetInstance()->SetProj(proj);
	}
}
