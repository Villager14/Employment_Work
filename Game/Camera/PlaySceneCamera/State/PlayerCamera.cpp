/*
* @file		PlayerCamera.cpp
* @brief	プレイヤーのカメラ
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(m_playerCameraManager->GetInformation()->ANGLE_Y_MIN);
}

void PlayerCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		eyeの作製
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->GetPlayerHeight() + 
									 m_playerCameraManager->GetInformation()->GetShaekHeadVelocity(),
									 m_playerCameraManager->GetInformation()->GetAngle());

	m_playerCameraManager->GetInformation()->SetSheakHeadVelocity(DirectX::SimpleMath::Vector3::Zero);

	//		状態遷移の確認
	ChangeStateConfirmation();

	//		頭を振っていない状態にする
	m_playerCameraManager->GetInformation()->SetShackHeadJudgement(false);
}

void PlayerCamera::Finalize()
{
}

void PlayerCamera::ChangeStateConfirmation()
{
	//		死亡している場合
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		死亡カメラにする
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Death);
	}

	//		次のシーンを選んだ際
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		//		ゴールカメラにする
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Goal);
	}
}
