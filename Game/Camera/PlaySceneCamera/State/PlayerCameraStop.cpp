/*
* @file		PlayerCameraStop.cpp
* @brief	�v���C���[�����Ȃ��̃J����
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
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void PlayerCameraStop::Update()
{
	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->GetPlayerHeight(),
									m_playerCameraManager->GetInformation()->GetAngle());

	//		�J�ڂ̊m�F
	ChangeStateConfirmation();
}

void PlayerCameraStop::Finalize()
{
}

void PlayerCameraStop::ChangeStateConfirmation()
{
	//		�v���C���[�̒�~���I�������Ƃ�
	//if (!m_playerCameraManager->GetPlayerInformationCamera()->GetCameraStop())
	//{
	//	//		�v���C���[�J�����ɐ؂�ւ���
	//	m_playerCameraManager->ChangeState(
	//		m_playerCameraManager->CameraType::Standard);
	//}

	//		�����J�����ړ��ʂ��O���傫��������
	//if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() > 0.0f)
	//{
	//	//		�Ǒ���J�����ɐ؂�ւ���
	//	m_playerCameraManager->ChangeState(
	//		m_playerCameraManager->CameraType::WallWalk);
	//}

	if (!m_playerCameraManager->GetInformation()->GetStopJudgement())
	{
		//		�v���C���[�J�����ɐ؂�ւ���
		m_playerCameraManager->ChangeState(
		m_playerCameraManager->CameraType::Standard);
	}
	else
	{
		m_playerCameraManager->GetInformation()->SetStopJudgement(false);
	}

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
