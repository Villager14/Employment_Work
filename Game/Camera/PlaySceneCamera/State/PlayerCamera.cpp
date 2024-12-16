/*
* @file		PlayerCamera.cpp
* @brief	�v���C���[�̃J����
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
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(m_playerCameraManager->GetInformation()->ANGLE_Y_MIN);
}

void PlayerCamera::Update()
{
	m_playerCameraManager->CameraMove();

	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->GetPlayerHeight() + 
									 m_playerCameraManager->GetInformation()->GetShaekHeadVelocity(),
									 m_playerCameraManager->GetInformation()->GetAngle());

	m_playerCameraManager->GetInformation()->SetSheakHeadVelocity(DirectX::SimpleMath::Vector3::Zero);

	//		��ԑJ�ڂ̊m�F
	ChangeStateConfirmation();

	//		����U���Ă��Ȃ���Ԃɂ���
	m_playerCameraManager->GetInformation()->SetShackHeadJudgement(false);
}

void PlayerCamera::Finalize()
{
}

void PlayerCamera::ChangeStateConfirmation()
{
	//		���S���Ă���ꍇ
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		���S�J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Death);
	}

	//		���̃V�[����I�񂾍�
	if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		//		�S�[���J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Goal);
	}
}
