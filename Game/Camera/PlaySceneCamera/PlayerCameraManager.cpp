/*
* @file		PlayerCameraManager.cpp
* @brief	�v���C���[�̃J�����̃}�l�[�W���[
* @author	Morita
* @date		2024/05/08
*/

#include "pch.h"

#include "PlayerCameraManager.h"

PlayerCameraManager::PlayerCameraManager()
	:
	m_state{}
{
}

PlayerCameraManager::~PlayerCameraManager()
{
}

void PlayerCameraManager::Initialize()
{
	//		�f�o�b�N�J�����̐���
	m_debugCamera = std::make_unique<DebugCamera>(this);
	//		�v���C���[�J�����̐���
	m_playerCamera = std::make_unique<PlayerCamera>(this);
	//		�v���C���[�Ǒ���J�����̐���
	m_playerWallWalkCamera = std::make_unique<PlayerWallWalkCamera>(this);

	//		�����J�����̑I��
	m_state = m_playerCamera.get();

	//		����������
	m_state->Initialize();

	/*
	*	����p70�x
	*
	*	�߂�����0.1f
	* �@��������500.0f
	*/
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(50.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 500.0f);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
}

void PlayerCameraManager::Update(PlayerInformationCamera* playerInformationCamera)
{
	m_playerInformationCamera = playerInformationCamera;

	//		�J�����̍X�V����
	m_state->Update();

	ViewingAngle();
}

void PlayerCameraManager::Finalize()
{
}

void PlayerCameraManager::CameraMove()
{
	//		�}�E�X�̑��Έʒu����ړ��ʂ��o��
	float x = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().x);
	float y = static_cast<float>(LibrarySingleton::GetInstance()->GetButtonStateTracker()->GetLastState().y);

	//		�J�����̈ړ��ʂ𑫂�
	m_angle.x += x * CAMERA_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
	m_angle.y += -y * (CAMERA_SPEED / 2.0f) * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		���_�ړ��̐���
	m_angle.y = Library::Clamp(m_angle.y, ANGLE_Y_MIN, ANGLE_Y_MAX);
	
}

void PlayerCameraManager::ChangeState(IPlayerCamera* state)
{
	//		������ԂȂ珈�������Ȃ�
	if (m_state == state) return;

	//		���݂̏�Ԃ̏I���������s��
	m_state->Finalize();

	//		�V������Ԃɂ���
	m_state = state;

	//		�V������Ԃ̏�����������
	m_state->Initialize();
}

void PlayerCameraManager::ViewingAngle()
{
	if (m_playerInformationCamera->GetAcceleration().Length() > 50.0f)
	{
		float time = Library::Clamp(((m_playerInformationCamera->GetAcceleration().Length() - 50.0f) / 60.0f), 0.0f, 1.0f);

		float viewAnge = Library::Lerp(50.0f, 55.0f, time);

		/*
		*	����p70�x
		*
		*	�߂�����0.1f
		* �@��������500.0f
		*/
		DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
			CreatePerspectiveFieldOfView
			(DirectX::XMConvertToRadians(viewAnge), LibrarySingleton::GetInstance()->GetScreenSize().x /
				LibrarySingleton::GetInstance()->GetScreenSize().y,
				0.1f, 500.0f);

		//		�v���W�F�N�V�����s���ݒ肷��
		LibrarySingleton::GetInstance()->SetProj(proj);
	}
}
