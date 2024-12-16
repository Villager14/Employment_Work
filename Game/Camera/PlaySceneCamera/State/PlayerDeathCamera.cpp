/*
* @file		PlayerDeathCamera.cpp
* @brief	プレイヤーの死亡カメラ
* @author	Morita
* @date		2024/05/22
*/

#include "pch.h"

#include "PlayerDeathCamera.h"

PlayerDeathCamera::PlayerDeathCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerDeathCamera::~PlayerDeathCamera()
{
}

void PlayerDeathCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerDeathCamera::Update()
{
	//		eyeの作製
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->
		GetPlayerHeight(), m_playerCameraManager->GetInformation()->GetAngle());

	//		遷移の確認
	ChangeStateConfirmation();
}

void PlayerDeathCamera::Finalize()
{
	//		カメラの角度をリセットする
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);
}

void PlayerDeathCamera::ChangeStateConfirmation()
{
	//		もし死亡状態が解除されたら
	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		スタートカメラ
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Start);
	}
}
