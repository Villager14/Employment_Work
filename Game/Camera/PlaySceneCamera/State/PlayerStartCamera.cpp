/*
* @file		PlayerStartCamera.h
* @brief	�v���C���[�X�^�[�g�J����
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStartCamera.h"

PlayerStartCamera::PlayerStartCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f),
	m_firstViewJudgement(true)
{
}

PlayerStartCamera::~PlayerStartCamera()
{
}

void PlayerStartCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	//		�Q�[���X�^�[�g�t���O���I�t�ɂ���
	m_playerCameraManager->GetGameManager()->FalseFlag(GameManager::GameStart);

	if (!m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::StartLimitView))
	{
		m_firstViewJudgement = true;
	}
}

void PlayerStartCamera::Update()
{
	Move();

	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->
		GetPlayerHeight(), m_playerCameraManager->GetInformation()->GetAngle());

	//		��ԑJ�ڊm�F
	ChangeStateConfirmation();
}

void PlayerStartCamera::Finalize()
{
	m_time = 0.0f;

	m_playerCameraManager->GetInformation()->SetAngle({ m_playerCameraManager->GetInformation()->GetStartDirection(), 0.0f});


}

void PlayerStartCamera::Move()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * ANGLE_UP_SPEED;

	m_time = Library::Clamp(m_time, 0.0f, 1.0f);

	//		�p�x��ݒ肷��
	m_playerCameraManager->GetInformation()->SetAngle(
		{ m_playerCameraManager->GetInformation()->GetStartDirection(),
		Library::Lerp(DOWN_ANGLE, 0.0f, EasingProcess::EaseOutQuart(m_time))});
}

void PlayerStartCamera::ChangeStateConfirmation()
{
	if (m_time >= STATE_CHANGE_TIME)
	{
		/*
		//		������Ԃ̏ꍇ
		if (m_firstViewJudgement)
		{
			m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::StartLimitView);

			if (m_playerCameraManager->GetGameManager()->FlagJudgement(GameManager::GameStart))
			{
				m_firstViewJudgement = false;

				//		�X�^���_�[�h�J�����ɂ���
				m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);
			}

			return;
		}
		//*/

		//		�X�^���_�[�h�J�����ɂ���
		m_playerCameraManager->ChangeState(m_playerCameraManager->CameraType::Standard);

		//		�Q�[���X�^�[�g�t���O���I���ɂ���
		m_playerCameraManager->GetGameManager()->TrueFlag(GameManager::GameStart);
	}
}
