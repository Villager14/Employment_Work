/*
* @file		PlayerGoalCamera.cpp
* @brief	プレイヤーのゴールカメラ
* @author	Morita
* @date		2024/06/27
*/

#include "pch.h"

#include "PlayerGoalCamera.h"

PlayerGoalCamera::PlayerGoalCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_elapsedTime(0.0f),
	m_downElapsedTime(0.0f)
{
}

PlayerGoalCamera::~PlayerGoalCamera()
{
}

void PlayerGoalCamera::Initialize()
{
	//		マウスを相対参照にする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_angle = m_playerCameraManager->GetInformation()->GetAngle();

	m_elapsedTime = 0.0f;

	m_downElapsedTime = 0.0f;
}

void PlayerGoalCamera::Update()
{
	CameraMove();

	//		eyeの作製
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->
		GetPlayerHeight(), m_playerCameraManager->GetInformation()->GetAngle());
}

void PlayerGoalCamera::Finalize()
{
	//		カメラの角度をリセットする
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);

}

void PlayerGoalCamera::CameraMove()
{
	if (m_elapsedTime < PARALLEL_MAXIMUM_TIME)
	{
		//		経過時間
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * PARALLEL_MAXIMUM_SPEED;

		if (m_elapsedTime <= 1.0f)
		{
			//		カメラを平行にする
			m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(m_angle.y, 0.0f, m_elapsedTime) });
		}
	}
	else
	{
		m_downElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_downElapsedTime = Library::Clamp(m_downElapsedTime, 0.0f, 1.0f);

		//		下を向く
		m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(0.0f, DOWN_VIEW_ANGLE, m_downElapsedTime) });
	}
}