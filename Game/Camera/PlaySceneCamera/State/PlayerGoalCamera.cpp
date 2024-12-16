/*
* @file		PlayerGoalCamera.cpp
* @brief	�v���C���[�̃S�[���J����
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
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_angle = m_playerCameraManager->GetInformation()->GetAngle();

	m_elapsedTime = 0.0f;

	m_downElapsedTime = 0.0f;
}

void PlayerGoalCamera::Update()
{
	CameraMove();

	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->
		GetPlayerHeight(), m_playerCameraManager->GetInformation()->GetAngle());
}

void PlayerGoalCamera::Finalize()
{
	//		�J�����̊p�x�����Z�b�g����
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);

}

void PlayerGoalCamera::CameraMove()
{
	if (m_elapsedTime < PARALLEL_MAXIMUM_TIME)
	{
		//		�o�ߎ���
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * PARALLEL_MAXIMUM_SPEED;

		if (m_elapsedTime <= 1.0f)
		{
			//		�J�����𕽍s�ɂ���
			m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(m_angle.y, 0.0f, m_elapsedTime) });
		}
	}
	else
	{
		m_downElapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_downElapsedTime = Library::Clamp(m_downElapsedTime, 0.0f, 1.0f);

		//		��������
		m_playerCameraManager->GetInformation()->SetAngle({ m_angle.x ,Library::Lerp(0.0f, DOWN_VIEW_ANGLE, m_downElapsedTime) });
	}
}