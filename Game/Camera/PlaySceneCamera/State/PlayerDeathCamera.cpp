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
	//		�f�O���[���烉�W�A���֍s��ɂ���
	DirectX::SimpleMath::Matrix matrixY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().x));
	DirectX::SimpleMath::Matrix matrixX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_playerCameraManager->GetInformation()->GetAngle().y));

	//		�����Ă���p�x�ɂ���
	DirectX::SimpleMath::Matrix rotation = matrixY * matrixX;

	//		�J�������W
	DirectX::SimpleMath::Vector3 position = m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Transform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), rotation.Invert());

	//		�^�[�Q�b�g�Ƀv���C���[�̍��W�𑫂�
	target += m_playerCameraManager->GetPlayerInformationCamera()->GetPlayerHeight();

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	(position, target, up));

	//		�����x�N�g����ݒ肷��
	m_playerCameraManager->GetInformation()->SetViewVelocity(target - position);

	//		�������S��Ԃ��������ꂽ��
	if (!m_playerCameraManager->GetGameManager()->GetDeathJudgement() > 0.0f)
	{
		//		�X�^�[�g�J����
		m_playerCameraManager->ChangeState(
			m_playerCameraManager->GetStartCamera());
	}
}

void PlayerDeathCamera::Finalize()
{
	//		�J�����̊p�x�����Z�b�g����
	m_playerCameraManager->GetInformation()->SetAngle(DirectX::SimpleMath::Vector2::Zero);
}