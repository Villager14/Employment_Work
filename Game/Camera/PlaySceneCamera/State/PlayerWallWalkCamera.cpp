/*
* @file		PlayerCamera.cpp
* @brief	�v���C���[�̃J����
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayerWallWalkCamera.h"

PlayerWallWalkCamera::PlayerWallWalkCamera(PlayerCameraManager* playerCameraManager)
	:
	m_playerCameraManager(playerCameraManager),
	m_time(0.0f)
{
}

PlayerWallWalkCamera::~PlayerWallWalkCamera()
{
}

void PlayerWallWalkCamera::Initialize()
{
	//		�}�E�X�𑊑ΎQ�Ƃɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);

	m_playerCameraManager->GetInformation()->SetCameraAngleMin(-20.0f);
}

void PlayerWallWalkCamera::Update()
{
	Move();

	DirectX::SimpleMath::Vector3 up = m_playerCameraManager->GetInformation()->GetWallNormalize(); //m_playerCameraManager->GetPlayerInformationCamera()->GetWallWalkNormalize();

	float length2 = m_playerCameraManager->GetInformation()->GetWallHeight() / 5.0f;

	up = DirectX::SimpleMath::Vector3::Lerp(DirectX::SimpleMath::Vector3::Zero, up * 0.1f, length2);

	up.y = Library::Lerp(1.0f, 0.9f, length2);

	//		eye�̍쐻
	m_playerCameraManager->CreateEye(m_playerCameraManager->GetInformation()->GetPlayerHeight(),
		m_playerCameraManager->GetInformation()->GetAngle(), up);

	ChangeStateConfirmation();
}

void PlayerWallWalkCamera::Finalize()
{
	m_time = 0.0f;
}

void PlayerWallWalkCamera::RadianConversion(float* cameraangle, float* velocityRadian)
{
	int radian = static_cast<int>(DirectX::XMConvertToDegrees(
		atan2(m_playerCameraManager->GetInformation()->GetDirection().z,
			m_playerCameraManager->GetInformation()->GetDirection().x)));

	//		�J�����̊p�x���󂯎��
	int angle = static_cast<int>(m_playerCameraManager->GetInformation()->GetAngle().x);

	//		�͈͂�0~�R�U�O�ɂ���
	radian = (radian - 90) % 360;
	angle %= 360;

	//		�O�ȉ��̏ꍇ360�𑫂����̐��ɂ���
	if (angle < 0.0f) { angle += 360; }
	if (radian < 0.0f) { radian += 360; }

	//		�ŒZ�����ňړ����邽�߁i+ -�j(- +)�̎�(+ -)�̕���360�𑫂�
	if (radian < 90 && angle > 270)
	{
		radian += 360;
	}
	else if (angle < 90.0f && radian > 270)
	{
		angle += 360;
	}

	*cameraangle = static_cast<float>(angle);
	*velocityRadian = static_cast<float>(radian);
}

void PlayerWallWalkCamera::ChangeStateConfirmation()
{
	//		�����J�����ړ��ʂ��O�ȉ��̏ꍇ
	//if (m_playerCameraManager->GetPlayerInformationCamera()->GetHeadMove() <= 0.0f)
	//{
	//	//		�v���C���[�J�����ɐ؂�ւ���
	//	m_playerCameraManager->ChangeState(
	//		m_playerCameraManager->CameraType::Standard);
	//}

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

void PlayerWallWalkCamera::Move()
{
	if (m_time < 1.0f)
	{
		//		�o�ߎ��� ���@�T
		m_time += LibrarySingleton::GetInstance()->GetElpsedTime() * 5.0f;

		//		��b�ȏ�ɂȂ�Ȃ��悤�ɂ���
		m_time = Library::Clamp(m_time, 0.0f, 1.0f);

		float angle = 0;
		float radian = 0;

		//		�J�����p�x�ƈړ��p�x���󂯎��
		RadianConversion(&angle, &radian);

		//		�J�����̊p�x��ݒ肷��
		m_playerCameraManager->GetInformation()->SetAngle({
			Library::Lerp(angle, radian, m_time),
			m_playerCameraManager->GetInformation()->GetAngle().y });
	}
	else
	{
		//		�ʏ�̃J�����Ɠ�������
		m_playerCameraManager->CameraMove();
	}
}
