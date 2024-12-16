/*
* @file		PlayerCameraStop.cpp
* @brief	プレイヤー動かないのカメラ
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"

#include "PlayerCameraStop.h"

PlayerCameraStop::PlayerCameraStop(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager)
{
}

PlayerCameraStop::~PlayerCameraStop()
{
}

void PlayerCameraStop::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerCameraStop::Update()
{
	//		eyeの作製
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->GetPlayerHeight(),
									m_playerCameraManager->GetInformation()->GetAngle());

	//		遷移の確認
	ChangeStateConfirmation();
}

void PlayerCameraStop::Finalize()
{
}

void PlayerCameraStop::ChangeStateConfirmation()
{
	//		プレイヤーの停止が終了したとき
	//if (!m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	//{
	//	//		プレイヤーカメラに切り替える
	//	m_playerCameraManager->ChangeState(
	//		m_playerCameraManager->CameraType::Standard);
	//}

	//		もしカメラ移動量が０より大きかったら
	//if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() > 0.0f)
	//{
	//	//		壁走りカメラに切り替える
	//	m_playerCameraManager->ChangeState(
	//		m_playerCameraManager->CameraType::WallWalk);
	//}

	if (!m_playerCameraManager->GetInformation()->GetStopJudgement())
	{
		//		プレイヤーカメラに切り替える
		m_playerCameraManager->ChangeState(
		m_playerCameraManager->CameraType::Standard);
	}
	else
	{
		m_playerCameraManager->GetInformation()->SetStopJudgement(false);
	}

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
