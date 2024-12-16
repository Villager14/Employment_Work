/*
* @file		PlayerDeathCamera.cpp
* @brief	�v���C���[�̎��S�J����
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
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerDeathCamera::Update()
{
	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->
		GetPlayerHeight(), m_playerCameraManager->GetInformation()->GetAngle());

	//		�J�ڂ̊m�F
	ChangeStateConfirmation();
}

void PlayerDeathCamera::Finalize()
{
	//		�J�����̊p�x�����Z�b�g����
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);
}

void PlayerDeathCamera::ChangeStateConfirmation()
{
	//		�������S��Ԃ��������ꂽ��
	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		�X�^�[�g�J����
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->CameraType::Start);
	}
}
